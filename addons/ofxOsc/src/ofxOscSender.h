/*
 
 Copyright (c) 2007-2009, Damian Stewart
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * Neither the name of the developer nor the
 names of its contributors may be used to endorse or promote products
 derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY DAMIAN STEWART ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL DAMIAN STEWART BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

/**

ofxOscSender

an ofxOscSender sends messages to a single host/port

*/

#include "OscTypes.h"
#include "OscOutboundPacketStream.h"
#include "UdpSocket.h"

#include "ofxOscBundle.h"
#include "ofParameter.h"
#include "ofParameterGroup.h"

class ofxOscSender{
public:

	ofxOscSender();
	ofxOscSender(const ofxOscSender & mom);
	ofxOscSender& operator=(const ofxOscSender & mom);
	/// for operator= and copy constructor
	ofxOscSender& copy(const ofxOscSender& other);

	/// send messages to hostname and port
	void setup(const string &hostname, int port);
	
	/// clear the sender 
	void clear();

	/// send the given message
	void sendMessage(const ofxOscMessage& message, bool wrapInBundle = true);
	
	/// send the given bundle
	void sendBundle(const ofxOscBundle& bundle);
	
	/// creates a message using an ofParameter
	void sendParameter(const ofAbstractParameter & parameter);

	/// return current hostname or "" if setup was not called
	string getHostname();

	/// return current port or 0 if setup was not called
	int getPort();
	
	/// disables broadcast capabilities, usually call this before setup
	void disableBroadcast();

	/// enabled broadcast capabilities (usually no need to call this, enabled by default)
	void enableBroadcast();

private:
		
	// helper methods for constructing messages
	void appendBundle(const ofxOscBundle& bundle, osc::OutboundPacketStream& p);
	void appendMessage(const ofxOscMessage& message, osc::OutboundPacketStream& p);
	void appendParameter(ofxOscBundle & bundle, const ofAbstractParameter & parameter, const string &address);
	void appendParameter(ofxOscMessage & msg, const ofAbstractParameter & parameter, const string &address);

	std::unique_ptr<osc::UdpTransmitSocket> socket;
	bool broadcast;
	string hostname;
	int port;
};
