#include "GameState.h"

#include <iostream>

using namespace std;

int getInteger(string str, size_t pos) {
	return ((unsigned char)str[pos] * (1 << 0)) + ((unsigned char)str[pos+1] * (1 << 8)) + ((unsigned char)str[pos+2] * (1 << 16)) + ((unsigned char)str[pos+3] * (1 << 24)) - 16777216;
};

float getFloat(string str, size_t pos) {
	int ip = ((unsigned char)str[pos] * (1 << 0)) + ((unsigned char)str[pos+1] * (1 << 8)) + ((unsigned char)str[pos+2] * (1 << 16)) + ((unsigned char)str[pos+3] * (1 << 24)) - 16777216;
	int fp = ((unsigned char)str[pos+4] * (1 << 0)) + ((unsigned char)str[pos+5] * (1 << 8)) + ((unsigned char)str[pos+6] * (1 << 16));
	return ip + fp / 16777216.f;
};

GameState::GameState()
{
}

GameState::~GameState()
{
}

void GameState::parse(std::string msg) {
	/*
	float2net(o.x) + float2net(o.y) + float2net(o.vx) + float2net(o.vy) + float2net(o.r) +
    float2net(o.rot) + float2net(o.a) + int2net(o.id) + float2net(o.cd);
	*/
	players.resize(0);
	turrets.resize(0);
	obstacles.resize(0);
	lasers.resize(0);
	size_t pos = 0;

	int pc = getInteger(msg, pos);
	pos += 4;
	for (int i = 0; i < pc; i++) {
		GameObject o;
		o.x = getFloat(msg, pos);
		pos += 7;
		o.y = getFloat(msg, pos);
		pos += 7;
		o.vx = getFloat(msg, pos);
		pos += 7;
		o.vy = getFloat(msg, pos);
		pos += 7;
		o.radius = getFloat(msg, pos);
		pos += 7;
		o.rotation = getFloat(msg, pos);
		pos += 7;
		o.acceleration = getFloat(msg, pos);
		pos += 7;
		o.id = getInteger(msg, pos);
		pos += 4;
		o.cooldown = getFloat(msg, pos);
		pos += 7;
		players.push_back(o);
	}

	int tc = getInteger(msg, pos);
	pos += 4;
	for (int i = 0; i < tc; i++) {
		GameObject o;
		o.x = getFloat(msg, pos);
		pos += 7;
		o.y = getFloat(msg, pos);
		pos += 7;
		o.vx = getFloat(msg, pos);
		pos += 7;
		o.vy = getFloat(msg, pos);
		pos += 7;
		o.radius = getFloat(msg, pos);
		pos += 7;
		o.rotation = getFloat(msg, pos);
		pos += 7;
		o.acceleration = getFloat(msg, pos);
		pos += 7;
		o.id = getInteger(msg, pos);
		pos += 4;
		o.cooldown = getFloat(msg, pos);
		pos += 7;
		turrets.push_back(o);
	}

	int oc = getInteger(msg, pos);
	pos += 4;
	for (int i = 0; i < oc; i++) {
		GameObject o;
		o.x = getFloat(msg, pos);
		pos += 7;
		o.y = getFloat(msg, pos);
		pos += 7;
		o.vx = getFloat(msg, pos);
		pos += 7;
		o.vy = getFloat(msg, pos);
		pos += 7;
		o.radius = getFloat(msg, pos);
		pos += 7;
		o.rotation = getFloat(msg, pos);
		pos += 7;
		o.acceleration = getFloat(msg, pos);
		pos += 7;
		o.id = getInteger(msg, pos);
		pos += 4;
		o.cooldown = getFloat(msg, pos);
		pos += 7;
		obstacles.push_back(o);
	}

	int lc = getInteger(msg, pos);
	pos += 4;
	for (int i = 0; i < lc; i++) {
		GameObject o;
		o.x = getFloat(msg, pos);
		pos += 7;
		o.y = getFloat(msg, pos);
		pos += 7;
		o.vx = getFloat(msg, pos);
		pos += 7;
		o.vy = getFloat(msg, pos);
		pos += 7;
		o.radius = getFloat(msg, pos);
		pos += 7;
		o.rotation = getFloat(msg, pos);
		pos += 7;
		o.acceleration = getFloat(msg, pos);
		pos += 7;
		o.id = getInteger(msg, pos);
		pos += 4;
		o.cooldown = getFloat(msg, pos);
		pos += 7;
		lasers.push_back(o);
	}
}

void GameState::print() {
	cout << "Players:" << endl;
	for (size_t i = 0; i < players.size(); i++) {
		cout << "    x: " << players[i].x << endl;
		cout << "    y: " << players[i].y << endl;
		cout << "    vx: " << players[i].vx << endl;
		cout << "    vy: " << players[i].vy << endl;
		cout << "    r: " << players[i].radius << endl;
		cout << "    rot: " << players[i].rotation << endl;
		cout << "    a: " << players[i].acceleration << endl;
		cout << "    id: " << players[i].id << endl;
		cout << "    cd: " << players[i].cooldown << endl;
		cout << endl;
	}
	cout << endl;

	cout << "Turrets:" << endl;
	for (size_t i = 0; i < turrets.size(); i++) {
		cout << "    x: " << turrets[i].x << endl;
		cout << "    y: " << turrets[i].y << endl;
		cout << "    vx: " << turrets[i].vx << endl;
		cout << "    vy: " << turrets[i].vy << endl;
		cout << "    r: " << turrets[i].radius << endl;
		cout << "    rot: " << turrets[i].rotation << endl;
		cout << "    a: " << turrets[i].acceleration << endl;
		cout << "    id: " << turrets[i].id << endl;
		cout << "    cd: " << turrets[i].cooldown << endl;
		cout << endl;
	}
	cout << endl;

	cout << "Obstacles:" << endl;
	for (size_t i = 0; i < obstacles.size(); i++) {
		cout << "    x: " << obstacles[i].x << endl;
		cout << "    y: " << obstacles[i].y << endl;
		cout << "    vx: " << obstacles[i].vx << endl;
		cout << "    vy: " << obstacles[i].vy << endl;
		cout << "    r: " << obstacles[i].radius << endl;
		cout << "    rot: " << obstacles[i].rotation << endl;
		cout << "    a: " << obstacles[i].acceleration << endl;
		cout << "    id: " << obstacles[i].id << endl;
		cout << "    cd: " << obstacles[i].cooldown << endl;
		cout << endl;
	}
	cout << endl;

	cout << "Lasers:" << endl;
	for (size_t i = 0; i < lasers.size(); i++) {
		cout << "    x: " << lasers[i].x << endl;
		cout << "    y: " << lasers[i].y << endl;
		cout << "    vx: " << lasers[i].vx << endl;
		cout << "    vy: " << lasers[i].vy << endl;
		cout << "    r: " << lasers[i].radius << endl;
		cout << "    rot: " << lasers[i].rotation << endl;
		cout << "    a: " << lasers[i].acceleration << endl;
		cout << "    id: " << lasers[i].id << endl;
		cout << "    cd: " << lasers[i].cooldown << endl;
		cout << endl;
	}
	cout << endl;
}