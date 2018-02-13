/*
 * File: AlternateVoice.cpp
 * Date: 08.02.2018
 *
 * MIT License
 *
 * Copyright (c) 2018 AlternateVoice
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "AlternateVoice.h"

#include <iostream>
#include <enet/enet.h>

#include "HttpServer.h"
#include "Teamspeak.h"
#include "Client.h"

HttpServer *httpServer = nullptr;
Client *client = nullptr;

bool AlternateVoice_start() {
  ts3_log("Initialize", LogLevel_INFO);

  if (enet_initialize() != 0) {
    ts3_log("Unable to initialize ENet", LogLevel_ERROR);
    return false;
  }

  client = new Client();
  
  httpServer = new HttpServer();
  httpServer->open(23333);

  ts3_connect("ts.alternate-life.de", 9987, "");

  return true;
}

void AlternateVoice_stop() {
  ts3_log("Shutting down", LogLevel_INFO);

  httpServer->close();
  delete httpServer;

  delete client;

  enet_deinitialize();

  ts3_log("Shutdown", LogLevel_INFO);
}

bool AlternateVoice_connect(std::string host, uint16_t port, std::string uniqueIdentifier) {
  if (client->connect(host, port, uniqueIdentifier) == false) {
    ts3_log("Unable to connect to " + host + ":" + std::to_string(port), LogLevel_WARNING);
    return false;
  }

  return true;
}

void AlternateVoice_disconnect() {
  client->disconnect();
}
