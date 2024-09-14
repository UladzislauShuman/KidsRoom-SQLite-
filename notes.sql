CREATE TABLE IF NOT EXISTS toys
(
    id INTEGER SERIAL PRIMARY KEY,
    toy_tipe VARCHAR(50) DEFAULT 'Car',
    price INTEGER DEFAULT 999,
    gender VARCHAR(6) DEFAULT 'All',
    age INTEGER DEFAULT 0,
    how_much_can_play INTEGER DEFAULT 1,
    size VARCHAR(50) DEFAULT 'No inf',
    material VARCHAR(50) DEFAULT 'No inf'
);

CREATE TABLE IF NOT EXISTS car_characteristics
(
    toy_id INTEGER REFERENCES toys(id),
    model VARCHAR(50) DEFAULT 'No inf',
    body_type VARCHAR(50) DEFAULT 'No inf',
    color VARCHAR(50) DEFAULT 'No inf',
    is_radio BOOLEAN DEFAULT FALSE
);

CREATE TABLE IF NOT EXISTS cube_characteristics
(
    toy_id INTEGER REFERENCES toys(id),
    amount INTEGER DEFAULT 1,
    color VARCHAR(50) DEFAULT 'No inf',
    is_puzzle BOOLEAN DEFAULT false
);

CREATE TABLE IF NOT EXISTS dall_characteristics
(
    toy_id INTEGER REFERENCES toys(id),
    sobriquet VARCHAR(50) DEFAULT 'No inf',
    is_male BOOLEAN DEFAULT TRUE,
    is_human BOOLEAN DEFAULT FALSE
);

CREATE TABLE IF NOT EXISTS ball_characteristics
(
    toy_id INTEGER REFERENCES toys(id),
    ball_tipe VARCHAR(50) DEFAULT 'No inf',
    size_type INTEGER DEFAULT 0,
    color VARCHAR(50) DEFAULT 'No inf'
);



    -- INSERT INTO toys(
    --     -- id ,
    --     toy_tipe ,
    --     price ,
    --     gender ,
    --     age ,
    --     how_much_can_play ,
    --     size ,
    --     material
    -- )
    -- VALUES (
    --     'Car',
    --     99,
    --     'Male',
    --     11,
    --     12,
    --     'Medium',
    --     'skin'
    -- );

    -- INSERT INTO car_characteristics(
    --     toy_id,
    --     model ,
    --     body_type ,
    --     color,
    --     is_radio
    -- )
    -- VALUES(
    --     (SELECT id FROM toys ORDER BY id DESC LIMIT 1 ) ,
    --     'bugati',
    --     'big' ,
    --     'red',
    --     TRUE
    -- );

SELECT * from car_characteristics;