# API Token: pk_29118a1f11f0496b893a5b9db35f996d
# export API_KEY=pk_29118a1f11f0496b893a5b9db35f996d

import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/", methods=["GET", "POST"])
@login_required
def index():

    # Gets the info we want to display and sends it to index.html
    username = session.get('user_id')
    user_table = db.execute("SELECT symbol, name, shares, price, total FROM stocks WHERE id = :username", username=username)
    total = db.execute("SELECT cash FROM users WHERE id = :username", username=username)
    total = round(total[0]["cash"], 2)
    results = False
    #flash("incorrect username or password.")

    if request.method == "GET":
        return render_template("index.html", user_table=user_table, check=1, total=total)
    else:
        results = True
        dix = lookup(request.form.get("symbol"))
        if dix == None:
            return render_template("quote.html", results=results, t=1)
        else:
            return render_template("quote.html", results=results, dix=dix)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:

        # Check for input
        if not request.form.get("symbol"):
            flash("You must provide a stock symbol")
            return redirect("/buy")
            #return render_template("apology.html", top="403", bottom="ERROR: must prodive a stock symbol")
        elif not request.form.get("shares"):
            flash("You must provide an amount to purchase")
            return redirect("/buy")
            #return render_template("apology.html", top="403", bottom="ERROR: must provide the amount of shares you would like to purchase")
        if (request.form.get("shares").isdigit() == False) or int(request.form.get("shares")) < 1:
            flash("You must provide a positive integer amount")
            return redirect("/buy")
            #return render_template("apology.html", top="403", bottom="ERROR: must provide an positive integer amount")

        # Define all needed variables
        syy = request.form.get("symbol").upper()
        now = datetime.now()
        dtime = now.strftime("%d/%m/%Y %H:%M:%S") # CURRENT TIME
        check = True                            # BOOLEAN FOR DISPLAY IN HTML
        dix = lookup(syy) # NAME SYMBOL PRICE
        if dix == None:
            flash("Stock symbol does not exist in our records")
            return redirect("/buy")
            #return render_template("apology.html", top="403", bottom="ERROR: that stock symbol does not exist in our records")
        ammt = request.form.get("shares")           # AMMOUNT
        pur_total = float(ammt) * float(dix["price"]) # TOTAL PRICE OF PURCHASE
        username = session.get('user_id')           # USER ID
        total = db.execute("SELECT cash FROM users WHERE id = :username", username=username) # TOTAL CASH (total[0]["cash"])
        total = round(total[0]["cash"], 2)

        # Check for sufficient funds
        if pur_total > total:
            flash("You do not have sufficient funds to make the purchase")
            return redirect("/buy")
            #return render_template("apology.html", top="403", bottom="ERROR: you do not have sufficient funds")

        # Add transaction to history
        db.execute("INSERT INTO history (symbol, stocks, price, total, typebuy, id, time) VALUES (:syy, :ammt, :price, :total, 'Bought', :username, :time)", syy=syy, ammt=ammt, price=round(dix["price"], 2), total=round(pur_total, 2), username=username, time=dtime)

        # Check for duplicates
        checko = db.execute("SELECT symbol FROM stocks WHERE id = :username AND symbol = :syy", username=username, syy=syy)
        if len(checko) != 0:

            # Updates total total price
            new_total = total - pur_total
            db.execute("UPDATE users SET cash = :new_total WHERE id = :username", new_total=round(new_total, 2), username=username)

            # Adds shares and total
            current_ammt = db.execute("SELECT shares FROM stocks WHERE id = %s AND symbol = %s", (username, syy))
            ammt = int(ammt) + int(current_ammt[0]["shares"])
            pur_total = ammt * dix["price"]
            #return render_template("apology.html", top=current_ammt, bottom=" ")

            # Update database with all information
            db.execute("UPDATE stocks SET shares = :shares, total = :total, time = :dtime WHERE id = :id AND symbol = :symbol", shares=ammt, total=round(pur_total, 2), dtime=dtime, id=username, symbol=dix["symbol"])
            return redirect("/")

        else:

            # Updates total price
            new_total = total - pur_total
            db.execute("UPDATE users SET cash = :new_total WHERE id = :username", new_total=round(new_total, 2), username=username)

            # Update database with all information
            db.execute("INSERT INTO stocks (id, symbol, name, shares, price, total, time) VALUES (:id, :symbol, :name, :shares, :price, :total, :dtime)", id=username, symbol=dix["symbol"], name=dix["name"], shares=ammt, price=round(dix["price"], 2), total=round(pur_total, 2), dtime=dtime)
            return redirect("/")


@app.route("/history")
@login_required
def history():
    username = session.get('user_id')
    table = db.execute("SELECT * FROM history WHERE id = :username ORDER BY time DESC", username=username)
    return render_template("history.html", table=table)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    results = False
    if request.method == "GET":
        return render_template("quote.html", results=results)
    else:
        results = True
        dix = lookup(request.form.get("symbol"))
        if dix == None:
            return render_template("quote.html", results=results, t=1)
        else:
            return render_template("quote.html", results=results, dix=dix)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        # Checking for correct input
        if not request.form.get("username"):
            flash("You must provide a username")
            return redirect("/register")
            #return render_template("apology.html", top="403", bottom="ERROR: must provide a username")
        elif not request.form.get("password"):
            flash("You must provide a password")
            return redirect("/register")
            #return render_template("apology.html", top="403", bottom="ERROR: must provide a password")
        elif request.form.get("password") != request.form.get("confirmation"):
            flash("Passwords do not match")
            return redirect("/register")
            #return render_template("apology.html", top="403", bottom="ERROR: passwords do not match")
        else:

            # Get has instead of password to store in database
            hash = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)

            # Write new data in database
            db.execute("INSERT INTO users (username, hash) VALUES (:user, :hash)", user=request.form.get("username"), hash=hash)

            # Query database for username
            rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

            # Remember which user has logged in
            session["user_id"] = rows[0]["id"]

            # Redirect user to home page
            return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    if request.method == "GET":
        username = session.get('user_id')
        stocks = db.execute("SELECT symbol FROM stocks WHERE id = :username", username=username)
        return render_template("sell.html", stocks=stocks)
    else:

        # Check for input
        if not request.form.get("shares"):
            flash("You must provide an amount")
            return redirect("/sell")
            #return render_template("apology.html", top="403", bottom="ERROR: must provide an amount to sell")
        if (request.form.get("shares").isdigit() == False) or int(request.form.get("shares")) < 1:
            flash("You must provide a positive integer amount")
            return redirect("/sell")
            #return render_template("apology.html", top="403", bottom="ERROR: must provide an positive integer amount")

        # Get current number of stocks and define some variables
        now = datetime.now()
        dtime = now.strftime("%d/%m/%Y %H:%M:%S") # CURRENT TIME
        username = session.get('user_id')
        symb = request.form.get("symbol")
        share = request.form.get("shares") # for later use
        # return render_template("apology.html", top=symb, bottom=share) # WORKS

        stocc = db.execute("SELECT shares FROM stocks WHERE id = %s AND symbol = %s", (username, symb)) # symb needs to be in quotes
        stocc = stocc[0]["shares"]

        # Make sure user has enough stocks for the requested sell
        if int(share) > stocc:
            flash("You are trying to sell more stocks than you own")
            return redirect("/sell")
            #return render_template("apology.html", top="403", bottom="ERROR: you are trying to sell more stocks than you own")

        # Delete row if no stocks left after subtraction
        if int(share) == stocc:

            # Update "unused money"
            to_shares = db.execute("SELECT shares FROM stocks WHERE id = %s AND symbol = %s", username, symb)
            to_price = db.execute("SELECT price FROM stocks WHERE id = %s AND symbol = %s", username, symb)
            to_total = to_shares[0]["shares"] * to_price[0]["price"]
            total = db.execute("SELECT cash FROM users WHERE id = :username", username=username)
            total = round(total[0]["cash"], 2)
            added = int(share) * to_price[0]["price"]
            new_total = round((total + added), 2)
            db.execute("UPDATE users SET cash = :new_total WHERE id = :username", new_total=round(new_total, 2), username=username)

            # Add transaction to history
            db.execute("INSERT INTO history (symbol, stocks, price, total, typebuy, id, time) VALUES (:syy, :ammt, :price, :total, 'Sold', :username, :time)", syy=symb, ammt=share, price=round(to_price[0]["price"], 2), total=round(added, 2), username=username, time=dtime)

            db.execute("DELETE FROM stocks WHERE id = %s AND symbol = %s", (username, symb))
            return redirect("/")

        else:

            # Update row (total)
            total = stocc - int(share)
            db.execute("UPDATE stocks SET shares = %s WHERE id = %s AND symbol = %s", (total, username, symb))
            to_shares = db.execute("SELECT shares FROM stocks WHERE id = %s AND symbol = %s", username, symb)
            to_price = db.execute("SELECT price FROM stocks WHERE id = %s AND symbol = %s", username, symb)
            to_total = to_shares[0]["shares"] * to_price[0]["price"]
            db.execute("UPDATE stocks SET total = %s WHERE id = %s AND symbol = %s", (round(to_total, 2), username, symb))

            # Update "unused money"
            total = db.execute("SELECT cash FROM users WHERE id = :username", username=username)
            total = round(total[0]["cash"], 2)
            added = int(share) * to_price[0]["price"]
            new_total = round((total + added), 2)
            db.execute("UPDATE users SET cash = :new_total WHERE id = :username", new_total=round(new_total, 2), username=username)

            # Add transaction to history
            db.execute("INSERT INTO history (symbol, stocks, price, total, typebuy, id, time) VALUES (:syy, :ammt, :price, :total, 'Sold', :username, :time)", syy=symb, ammt=share, price=round(to_price[0]["price"], 2), total=round(added, 2), username=username, time=dtime)
            return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
