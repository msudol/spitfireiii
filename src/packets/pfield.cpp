//
// pfield.cpp
// Project Spitfire
//
// Copyright (c) 2014 Daizee (rensiadz at gmail dot com)
//
// This file is part of Spitfire.
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "pfield.h"
#include "../Server.h"
#include "../Client.h"
#include "../Map.h"
#include "../Tile.h"

pfield::pfield(Server * server, request & req, amf3object & obj)
	: packet(server, req, obj)
{

}

pfield::~pfield()
{

}

void pfield::process()
{
	obj2["data"] = amf3object();
	amf3object & data2 = obj2["data"];

	if (command == "getOtherFieldInfo")
	{
		int fieldid = data["fieldId"];

		obj2["cmd"] = "field.getOtherFieldInfo";

		amf3object bean;

		MULTILOCK2(M_MAP, M_CLIENTLIST, M_ALLIANCELIST);
		data2["bean"] = gserver->map->GetMapCastle(fieldid, req.conn->client_->m_clientnumber);
		UNLOCK(M_ALLIANCELIST);
		UNLOCK(M_CLIENTLIST);
		UNLOCK(M_MAP);

		//data2["errorMsg"] = "";
		data2["ok"] = 1;
		data2["packageId"] = 0.0f;

		gserver->SendObject(client, obj2);
		return;
	}
}



