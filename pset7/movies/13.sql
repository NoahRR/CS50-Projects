SELECT name FROM stars
JOIN people ON stars.person_id = people.id
WHERE movie_id IN (
SELECT movie_id FROM stars
JOIN people ON stars.person_id = people.id
WHERE name = "Kevin Bacon"
INTERSECT
SELECT movie_id FROM stars
JOIN people ON stars.person_id = people.id
WHERE birth = 1958)
INTERSECT
SELECT name FROM stars
JOIN people ON stars.person_id = people.id
WHERE name != "Kevin Bacon"