USE baza;

DROP TABLE IF EXISTS agentie;

CREATE TABLE agentie
(
    a_id INT(15),
    a_nume VARCHAR(30),
    a_url VARCHAR(50),
    a_timezone varchar(20)
);

DROP TABLE IF EXISTS orar;

CREATE TABLE orar
(
    id_serviciu INT(5),
    luni INT(1),
    marti INT(1),
    mirecuri INT(1),
    joi INT(1),
    vineri INT(1),
    sambata INT(1),
    duminica INT(1),
    data_incepere date,
    data_sfarsit date
);

DROP TABLE IF EXISTS rute; 

CREATE TABLE rute
(
    id_ruta INT(5),
    a_id INT(15),
    nume_s_ruta varchar(50),
    nume_l_ruta varchar(850),
    tip INT(3)
);

DROP TABLE IF EXISTS timp_opriri;

CREATE TABLE timp_opriri
(
    id_traseu INT(10),
    ora_plecare TIME,
    ora_finalizare TIME,
    id_oprire INT(10),
    secventa_opriri INT(5)
);

DROP TABLE IF EXISTS opriri;

CREATE TABLE opriri 
(
    id_oprire INT(10),
    nume_oprire char(30),
    lat_oprire float(13,10),
    lon_oprire float(13,10)
);

DROP TABLE IF EXISTS trasee;

CREATE TABLE trasee
(
    id_ruta INT(5),
    id_serviciu INT(5),
    id_traseu INT(10),
    nume_s_traseu varchar(3)
);
DROP TABLE IF EXISTS delay;
CREATE TABLE delay
(
    minute INT(10),
    id_ruta INT(5)
);

LOAD DATA LOCAL INFILE '/home/lucianpc/Desktop/retele/agentie.txt' INTO TABLE agentie FIELDS TERMINATED BY ',' IGNORE 1 LINES;
LOAD DATA LOCAL INFILE '/home/lucianpc/Desktop/retele/calendar.txt' INTO TABLE orar FIELDS TERMINATED BY ',' IGNORE 1 LINES;
LOAD DATA LOCAL INFILE '/home/lucianpc/Desktop/retele/rute.txt' INTO TABLE rute FIELDS TERMINATED BY ',' IGNORE 1 LINES;
LOAD DATA LOCAL INFILE '/home/lucianpc/Desktop/retele/timp_opriri.txt' INTO TABLE timp_opriri FIELDS TERMINATED BY ',' IGNORE 1 LINES;
LOAD DATA LOCAL INFILE '/home/lucianpc/Desktop/retele/opriri.txt' INTO TABLE opriri FIELDS TERMINATED BY ',' IGNORE 1 LINES;
LOAD DATA LOCAL INFILE '/home/lucianpc/Desktop/retele/trasee.txt' INTO TABLE trasee FIELDS TERMINATED BY ',' IGNORE 1 LINES;
