-- Keep a log of any SQL queries you execute as you solve the mystery.

-- the theft took place on July 28, 2020 and that it took place on Chamberlin Street.
-- looking the crime scene report >>

SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND year = 2020 AND street = 'Chamberlin Street';

-- retrived: Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. 
--Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
--checking interviews >>

SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28 AND year = 2020;

-- retrived: Jose | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
--Eugene | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
--Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
--Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- looking security log >>

SELECT id, activity, license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND year = 2020 AND hour = 10 AND minute >= 15 AND minute < 30;

--260 | exit | 5P2BI95
--261 | exit | 94KL13X
--262 | exit | 6P58WS2
--263 | exit | 4328GD8
--264 | exit | G412CB7
--265 | exit | L93JTIZ
--266 | exit | 322W7JE
--267 | exit | 0NTHK55

--looking ATM transactions >>

SELECT id, account_number, transaction_type, amount FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2020 AND atm_location = 'Fifer Street';

-- retrived: 
--246 | 28500762 | withdraw | 48
--264 | 28296815 | withdraw | 20
--266 | 76054385 | withdraw | 60
--267 | 49610011 | withdraw | 50
--269 | 16153065 | withdraw | 80
--275 | 86363979 | deposit | 10
--288 | 25506511 | withdraw | 20
--313 | 81061156 | withdraw | 30
--336 | 26013199 | withdraw | 35

SELECT id, caller, receiver FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2020 AND duration < 60;

--retrived:
--id | caller | receiver
--221 | (130) 555-0289 | (996) 555-8899
--224 | (499) 555-9472 | (892) 555-8872
--233 | (367) 555-5533 | (375) 555-8161
--251 | (499) 555-9472 | (717) 555-1342
--254 | (286) 555-6063 | (676) 555-6554
--255 | (770) 555-1861 | (725) 555-3243
--261 | (031) 555-6622 | (910) 555-3251
--279 | (826) 555-1652 | (066) 555-9701
--281 | (338) 555-6650 | (704) 555-2131

SELECT * FROM people WHERE phone_number = '(130) 555-0289';

--398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7

SELECT * FROM people WHERE phone_number = '(499) 555-9472';

--560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55

SELECT * FROM people WHERE phone_number = '(367) 555-5533';

--686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

SELECT * FROM people WHERE phone_number = '(286) 555-6063';

--449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58

SELECT * FROM people WHERE phone_number = '(770) 555-1861';

--514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE

SELECT * FROM people WHERE phone_number = '(031) 555-6622';

--907148 | Kimberly | (031) 555-6622 | 9628244268 | Q12B3Z3

SELECT * FROM people WHERE phone_number = '(826) 555-1652';

--395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN

SELECT * FROM people WHERE phone_number = '(338) 555-6650';

--438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0


--260 | exit | 5P2BI95
--261 | exit | 94KL13X Ernest                   --prime
--262 | exit | 6P58WS2
--263 | exit | 4328GD8
--264 | exit | G412CB7 Roger                     --SHORT LIST
--265 | exit | L93JTIZ
--266 | exit | 322W7JE Russell                  --prime
--267 | exit | 0NTHK55 Evelyn

SELECT * FROM bank_accounts JOIN people ON bank_accounts.person_id = people.id WHERE account_number = 28500762 OR account_number = 28296815 OR account_number = 76054385 OR account_number = 49610011 OR account_number = 16153065 OR account_number = 25506511 OR account_number = 81061156 OR account_number = 26013199;

--retrived >>
account_number | person_id | creation_year | id | name | phone_number | passport_number | license_plate
--49610011 | 686048 | 2010 | 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X        --prime
--26013199 | 514354 | 2012 | 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE       --prime
--16153065 | 458378 | 2012 | 458378 | Roy | (122) 555-4581 | 4408372428 | QX4YZN3
--28296815 | 395717 | 2014 | 395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
--25506511 | 396669 | 2014 | 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
--28500762 | 467400 | 2014 | 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
--76054385 | 449774 | 2015 | 449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
--81061156 | 438727 | 2018 | 438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0

SELECT * FROM people WHERE phone_number = '(725) 555-3243';

--847116 | Philip | (725) 555-3243 | 3391710505 | GW362R6

SELECT * FROM people WHERE phone_number = '(375) 555-8161';

--864400 | Berthold | (375) 555-8161 |  | 4V16VO0

SELECT *
FROM flights JOIN passengers ON flights.id = passengers.flight_id JOIN airports ON flights.origin_airport_id = airports.id
WHERE month = 7 AND day = 29 AND year = 2020 ORDER BY hour DESC;


--id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat | id | abbreviation | full_name | city
--18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0 | 18 | 2835165196 | 9C | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0 | 18 | 6131360461 | 2C | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0 | 18 | 3231999695 | 3C | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0 | 18 | 3592750733 | 4C | 8 | CSF | Fiftyville Regional Airport | Fiftyville   3592750733
--18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0 | 18 | 2626335085 | 5D | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0 | 18 | 6117294637 | 6B | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0 | 18 | 2996517496 | 7A | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--18 | 8 | 6 | 2020 | 7 | 29 | 16 | 0 | 18 | 3915621712 | 8D | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20 | 53 | 7894166154 | 9B | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20 | 53 | 6034823042 | 2C | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20 | 53 | 4408372428 | 3D | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20 | 53 | 2312901747 | 4D | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20 | 53 | 1151340634 | 5A | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20 | 53 | 8174538026 | 6D | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20 | 53 | 1050247273 | 7A | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--53 | 8 | 9 | 2020 | 7 | 29 | 15 | 20 | 53 | 7834357192 | 8C | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15 | 23 | 4149859587 | 7D | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15 | 23 | 9183348466 | 8A | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15 | 23 | 7378796210 | 9B | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15 | 23 | 7874488539 | 2C | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15 | 23 | 4195341387 | 3A | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15 | 23 | 6263461050 | 4A | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15 | 23 | 3231999695 | 5A | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--23 | 8 | 11 | 2020 | 7 | 29 | 12 | 15 | 23 | 7951366683 | 6B | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30 | 43 | 7597790505 | 7B | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30 | 43 | 6128131458 | 8A | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30 | 43 | 6264773605 | 9A | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30 | 43 | 3642612721 | 2C | 8 | CSF | Fiftyville Regional Airport | Fiftyville   
--43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30 | 43 | 4356447308 | 3B | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--43 | 8 | 1 | 2020 | 7 | 29 | 9 | 30 | 43 | 7441135547 | 4A | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 36 | 7214083635 | 2A | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 36 | 1695452385 | 3B | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 36 | 5773159633 | 4A | 8 | CSF | Fiftyville Regional Airport | Fiftyville   5773159633
--36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 36 | 1540955065 | 5C | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 36 | 8294398571 | 6C | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 36 | 1988161715 | 6D | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 36 | 9878712108 | 7A | 8 | CSF | Fiftyville Regional Airport | Fiftyville
--36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20 | 36 | 8496433585 | 7B | 8 | CSF | Fiftyville Regional Airport | Fiftyville

SELECT * FROM airports WHERE id = 4 OR id = 6;

--4 | LHR | Heathrow Airport | London       --prime
--6 | BOS | Logan International Airport | Boston