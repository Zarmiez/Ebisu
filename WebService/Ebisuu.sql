USE master;
GO

IF EXISTS(SELECT * FROM sysdatabases WHERE name ='Ebisuu')
BEGIN
	RAISERROR('Dropping existing Ebisuu database...',0,1)
	DROP DATABASE Ebisuu;
END
GO

CREATE DATABASE Ebisuu;
GO

USE Ebisuu;
GO
IF db_name() <> 'Ebisuu'
BEGIN
	RAISERROR('Use database failed...',22,127) WITH LOG
	DROP DATABASE Ebisuu;
END


EXEC sp_grantlogin 'IIS AppPool\Sales'
GO
EXEC sp_grantdbaccess 'IIS AppPool\Sales'
GO
EXEC sp_addrolemember 'db_datawriter', 'IIS AppPool\Sales'
GO
EXEC sp_addrolemember 'db_datawriter', 'IIS AppPool\Sales'
GO
EXEC sp_addrolemember 'db_datareader', 'IIS AppPool\Sales'
GO

CREATE ROLE [db_execproc] AUTHORIZATION [dbo]
GO
GRANT EXECUTE ON SCHEMA::dbo TO db_execproc;
GO
EXEC sp_addrolemember 'db_execproc', 'IIS AppPool\Sales'
GO


GO
CREATE TABLE cliente
(
id_cliente  INT NOT NULL PRIMARY KEY IDENTITY,
nombre NVARCHAR(25) NOT NULL,
direccion NVARCHAR(25) NOT NULL
);
GO
INSERT INTO cliente(nombre,direccion) VALUES ('Sin Cuenta','N/A');/*Usuario Creado para depositar a cliente sin tener cuenta*/
INSERT INTO cliente(nombre,direccion) VALUES ('Salvador Gonzalez','Enrique Segoviano 10');
INSERT INTO cliente(nombre,direccion) VALUES ('Maria Jose Guzman','Benito Juarez 22');
INSERT INTO cliente(nombre,direccion) VALUES ('Juan Rocha','Miguel Hidalgo 32');
GO

CREATE TABLE destinatario
(
id_destinatario INT NOT NULL PRIMARY KEY,
id_cliente INT NOT NULL REFERENCES cliente(id_cliente)
);
/*
GO
ALTER TABLE destinatario ADD FOREIGN KEY (id_cliente) REFERENCES cliente(id_cliente);

GO
INSERT INTO destinatario(id_destinatario,id_cliente) VALUES (3,1);
INSERT INTO destinatario(id_destinatario,id_cliente) VALUES (1,2);
INSERT INTO destinatario(id_destinatario,id_cliente) VALUES (2,3);
*/GO

CREATE TABLE sucursal
(
id_sucursal INT NOT NULL PRIMARY KEY,
id_gerente INT NOT NULL,
nombre_sucursal NVARCHAR(25) NOT NULL,
direccion NVARCHAR(25) NOT NULL,
);

GO
INSERT INTO sucursal(id_sucursal,id_gerente,nombre_sucursal,direccion) VALUES (00,000,'CUENTA GENERAL','MEXICO');
INSERT INTO sucursal(id_sucursal,id_gerente,nombre_sucursal,direccion) VALUES (33,999,'Salamanca','Av Reforma');
INSERT INTO sucursal(id_sucursal,id_gerente,nombre_sucursal,direccion) VALUES (34,969,'Irapuato','Av Insurgentes');
INSERT INTO sucursal(id_sucursal,id_gerente,nombre_sucursal,direccion) VALUES (35,999,'Leon','Plaza Altacia');
GO
--Tipo de cuenta: (A)Ahorro (E)Empresarial (U)Universitario (N)Corriente
CREATE TABLE cuenta
(

id_cuenta INT NOT NULL PRIMARY KEY IDENTITY,
pass NVARCHAR(20) NOT NULL,
edo_cuenta NVARCHAR NOT NULL,
tipo NVARCHAR(15) NOT NULL,
id_sucursal INT NOT NULL REFERENCES sucursal(id_sucursal),
balance FLOAT NOT NULL

);
GO
ALTER TABLE cuenta ADD FOREIGN KEY (id_sucursal) REFERENCES sucursal(id_sucursal);
GO
INSERT INTO cuenta(pass,edo_cuenta,tipo,id_sucursal,balance) VALUES('1234','H','NA',00,000.0);
INSERT INTO cuenta(pass,edo_cuenta,tipo,id_sucursal,balance) VALUES('1324','H','A',33,100.0);
INSERT INTO cuenta(pass,edo_cuenta,tipo,id_sucursal,balance) VALUES('1234','H','E',34,150.50);
INSERT INTO cuenta(pass,edo_cuenta,tipo,id_sucursal,balance) VALUES('1234','H','U',35,555);
GO

CREATE TABLE cajero
(
id_cajero INT NOT NULL PRIMARY KEY IDENTITY,
es_adm BIT NOT NULL,
nombre_cajero NVARCHAR(25) NOT NULL UNIQUE,
contraseña NVARCHAR(25) NOT NULL,
);
GO
INSERT INTO cajero(es_adm, nombre_cajero, contraseña) VALUES (1,'Nicolas Ponce','Banco10');
INSERT INTO cajero(es_adm, nombre_cajero, contraseña) VALUES (0,'Monica Herrera','Dinero2');
INSERT INTO cajero(es_adm, nombre_cajero, contraseña) VALUES (1,'Carolina Fuentes','Hola21');
GO
CREATE TABLE transaccion
(
id_transaccion INT NOT NULL PRIMARY KEY IDENTITY,
id_cuenta INT NOT NULL REFERENCES cuenta(id_cuenta),
id_destinatario INT NOT NULL REFERENCES cuenta(id_cuenta),
id_cajero INT NOT NULL REFERENCES cajero(id_cajero),
movimientos NVARCHAR(25) NOT NULL, --(P)ago,(R)etiro
fecha DATE NOT NULL DEFAULT GETDATE(),
monto INT NOT NULL,
);
GO
/*ALTER TABLE transaccion ADD FOREIGN KEY (id_destinatario) REFERENCES destinatario(id_destinatario);
*/
ALTER TABLE transaccion ADD FOREIGN KEY (id_cuenta) REFERENCES cuenta(id_cuenta);
ALTER TABLE transaccion ADD FOREIGN KEY (id_destinatario) REFERENCES cuenta(id_cuenta);
ALTER TABLE transaccion ADD FOREIGN KEY (id_cajero) REFERENCES cajero(id_cajero);
GO
INSERT INTO transaccion(id_cuenta,id_destinatario, id_cajero, movimientos, fecha, monto) VALUES (1,2,1,'P','20180525',115.00);
INSERT INTO transaccion(id_cuenta,id_destinatario, id_cajero, movimientos, fecha, monto) VALUES (2,3,2,'P','20180518',1500.00);
INSERT INTO transaccion(id_cuenta,id_destinatario, id_cajero, movimientos, fecha, monto) VALUES (3,2,1,'R','20180518',1500.00);

/*GO
CREATE TABLE historial
(
id_cliente INT NOT NULL REFERENCES cliente(id_cliente)PRIMARY KEY,
id_cuenta INT NOT NULL REFERENCES cuenta(id_cuenta),
id_sucursal INT NOT NULL REFERENCES sucursal(id_sucursal),
id_transaccion INT NOT NULL REFERENCES transaccion(id_transaccion),
fecha DATE NOT NULL DEFAULT GETDATE()
);
GO
ALTER TABLE historial ADD FOREIGN KEY (id_cliente) REFERENCES cliente(id_cliente);
ALTER TABLE historial ADD FOREIGN KEY (id_cuenta) REFERENCES cuenta(id_cuenta);
ALTER TABLE historial ADD FOREIGN KEY (id_sucursal) REFERENCES sucursal(id_sucursal);
ALTER TABLE historial ADD FOREIGN KEY (id_transaccion) REFERENCES transaccion(id_transaccion);

GO
INSERT INTO historial(id_cliente, id_cuenta, id_sucursal, id_transaccion, fecha) VALUES (1,3,33,1,'20180518');
INSERT INTO historial(id_cliente, id_cuenta, id_sucursal, id_transaccion, fecha) VALUES (2,2,34,2,'20180518');
INSERT INTO historial(id_cliente, id_cuenta, id_sucursal, id_transaccion, fecha) VALUES (3,1,35,3,'20180518');
*/GO
CREATE TABLE cuenta_cliente
(
id_cliente INT NOT NULL REFERENCES cliente(id_cliente),
id_cuenta INT NOT NULL REFERENCES cuenta(id_cuenta),
PRIMARY KEY(id_cliente,id_cuenta) 
);
GO
ALTER TABLE cuenta_cliente ADD FOREIGN KEY (id_cliente) REFERENCES cliente(id_cliente);
ALTER TABLE cuenta_cliente ADD FOREIGN KEY (id_cuenta) REFERENCES cuenta(id_cuenta);
GO
INSERT INTO cuenta_cliente(id_cliente,id_cuenta) VALUES (1,1);
INSERT INTO cuenta_cliente(id_cliente,id_cuenta) VALUES (2,2);
INSERT INTO cuenta_cliente(id_cliente,id_cuenta) VALUES (3,3);
/*INSERT INTO cuenta_cliente(id_cliente,id_cuenta) VALUES (4,4);
INSERT INTO cuenta_cliente(id_cliente,id_cuenta) VALUES (5,5);
*/
GO
CREATE VIEW historial
AS 
SELECT tra.id_transaccion AS TRANSACCIONNO,tra.fecha AS FECHA,tra.id_cuenta AS ID_CUENTA,cl.nombre AS NOMBRE_CLIENTE, tra.id_destinatario AS ID_DESTINATARIO, tra.movimientos AS MOVIMIENTO,tra.monto AS MONTO, tra.id_cajero AS ID_CAJERO, ca.nombre_cajero AS NOMBRE_CAJERO
FROM cliente cl,transaccion tra, cajero ca ,cuenta cu, cuenta_cliente cu_cl
WHERE  tra.id_cuenta=cu.id_cuenta
AND tra.id_cajero=ca.id_cajero
AND cu_cl.id_cliente=cl.id_cliente
AND cu_cl.id_cuenta=cu.id_cuenta

GO
SELECT * FROM historial
