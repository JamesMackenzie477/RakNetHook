#include "RakNetHook.h"

// Stores the connection password.
const char password[] = {
	0x37, 0x4f, 0x5e, 0x11, 0x6c, 0x45
};

// Defines the RakNet hook functions.

RakNet::StartupResult __fastcall RakHook::Startup(RakNet::RakPeerInterface* instance, PVOID trash, unsigned int maxConnections, RakNet::SocketDescriptor *socketDescriptors, unsigned socketDescriptorCount, int threadPriority)
{
	// Writes to the dump file.
	DumpFile << "Creating RakPeerInterface." << endl;

	// Detatches the hook to prevent recursion.
	pStartupHook->Detatch();
	// Calls the original function.
	RakNet::StartupResult Result = instance->Startup(maxConnections, socketDescriptors, socketDescriptorCount, threadPriority);
	// Attaches the hook.
	pStartupHook->Attach();
	// Returns the result.
	return Result;
}

RakNet::ConnectionAttemptResult __fastcall RakHook::Connect(RakNet::RakPeerInterface* instance, PVOID trash, const char* host, unsigned short remotePort, const char *passwordData, int passwordDataLength, RakNet::PublicKey *publicKey, unsigned connectionSocketIndex, unsigned sendConnectionAttemptCount, unsigned timeBetweenSendConnectionAttemptsMS, RakNet::TimeMS timeoutTime)
{
	// Writes to the dump file.
	DumpFile << "Connecting to: " << host << ":" << to_string(remotePort) << endl 
		<< "Password data: 0x" << to_string(passwordData, passwordDataLength) << endl 
		<< "Public key: " << (publicKey ? "True" : "False") << endl;

	// Detatches the hook to prevent recursion.
	pConnectHook->Detatch();
	// Calls the original function.
	RakNet::ConnectionAttemptResult Result = instance->Connect(host, remotePort, password, sizeof(password), publicKey, connectionSocketIndex, sendConnectionAttemptCount, timeBetweenSendConnectionAttemptsMS, timeoutTime);
	// Attaches the hook.
	pConnectHook->Attach();
	// Returns the result.
	return Result;
}

RakNet::uint32_t __fastcall RakHook::Send(RakNet::RakPeerInterface* instance, PVOID trash, const char *data, const int length, RakNet::PacketPriority priority, RakNet::PacketReliability reliability, char orderingChannel, const RakNet::AddressOrGUID systemIdentifier, bool broadcast, RakNet::uint32_t forceReceiptNumber)
{
	// Writes to the dump file.
	DumpFile << "Sending: " << string(data, length) << endl;

	// Detatches the hook to prevent recursion.
	pSendHook->Detatch();
	// Calls the original function.
	RakNet::uint32_t Result = instance->Send(data, length, priority, reliability, orderingChannel, systemIdentifier, broadcast, forceReceiptNumber);
	// Attaches the hook.
	pSendHook->Attach();
	// Returns the result.
	return Result;
}

void __fastcall RakHook::SendLoopback(RakNet::RakPeerInterface* instance, PVOID trash, const char *data, const int length)
{
	// Detatches the hook to prevent recursion.
	pSendLoopbackHook->Detatch();
	// Calls the original function.
	instance->SendLoopback(data, length);
	// Attaches the hook.
	pSendLoopbackHook->Attach();
}

const char UnknownMessage[] = {
	0x83, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x56, 0xa5, 0x8a, 0x00, 0x00, 0x00, 0x08, 0x00,
	0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x56, 0xa5, 0x8a, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x56, 0xa5, 0x8a, 0x00,
	0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x05,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x56, 0xa5,
	0x8a, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x56, 0xa5, 0x8a, 0x00, 0x00, 0x00, 0x08, 0x00,
	0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x56, 0xa5, 0xa1, 0x00, 0x00, 0x00,
	0x08, 0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x56, 0xa5, 0xa1, 0x00,
	0x00, 0x00, 0x08, 0xff, 0xff, 0xff, 0xff, 0x05,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x56, 0xa5,
	0xa1, 0x00, 0x00, 0x00, 0x08, 0xff, 0xff, 0xff,
	0xff, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x56, 0xa5, 0xa1, 0x00, 0x00, 0x00, 0x08, 0xff,
	0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x56, 0xa5, 0xa1, 0x00, 0x00, 0x00,
	0x08, 0xff, 0xff, 0xff, 0xff, 0x0b, 0x00, 0x00,
	0x00, 0x00, 0x02, 0x81, 0x00, 0x00, 0x00, 0x23,
	0x52, 0x42, 0x58, 0x36, 0x46, 0x36, 0x44, 0x32,
	0x35, 0x35, 0x38, 0x38, 0x30, 0x33, 0x41, 0x34,
	0x31, 0x37, 0x36, 0x42, 0x36, 0x34, 0x32, 0x32,
	0x34, 0x42, 0x30, 0x31, 0x35, 0x42, 0x43, 0x36,
	0x46, 0x33, 0x44, 0x7d, 0x08, 0x00, 0x00, 0x00,
	0xa4, 0x01, 0x18, 0x81, 0x00, 0x00, 0x00, 0x0b,
	0x68, 0x75, 0x6e, 0x74, 0x65, 0x72, 0x32, 0x34,
	0x39, 0x35, 0x37, 0xff, 0x00, 0xb8, 0x27, 0x08,
	0x4c, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f,
	0x2f, 0x61, 0x70, 0x69, 0x2e, 0x72, 0x6f, 0x62,
	0x6c, 0x6f, 0x78, 0x2e, 0x63, 0x6f, 0x6d, 0x2f,
	0x76, 0x31, 0x2e, 0x31, 0x2f, 0x61, 0x76, 0x61,
	0x74, 0x61, 0x72, 0x2d, 0x66, 0x65, 0x74, 0x63,
	0x68, 0x2f, 0x3f, 0x70, 0x6c, 0x61, 0x63, 0x65,
	0x49, 0x64, 0x3d, 0x31, 0x35, 0x34, 0x37, 0x36,
	0x31, 0x30, 0x34, 0x35, 0x37, 0x26, 0x75, 0x73,
	0x65, 0x72, 0x49, 0x64, 0x3d, 0x31, 0x39, 0x38,
	0x39, 0x37, 0x36, 0x38, 0x31, 0x09, 0xa2, 0xf5,
	0xfc, 0x12, 0x0a, 0x00, 0x1b, 0x05, 0x57, 0x69,
	0x6e, 0x33, 0x32, 0x1d, 0x05, 0x65, 0x6e, 0x2d,
	0x75, 0x73, 0x26, 0xa2, 0xf5, 0xfc, 0x12, 0x28,
	0xa2, 0xf5, 0xfc, 0x12, 0xff, 0x82, 0x00, 0x00,
	0x00, 0x23, 0x52, 0x42, 0x58, 0x42, 0x44, 0x36,
	0x43, 0x38, 0x36, 0x36, 0x35, 0x41, 0x37, 0x36,
	0x34, 0x34, 0x44, 0x33, 0x34, 0x39, 0x43, 0x37,
	0x44, 0x42, 0x41, 0x33, 0x39, 0x42, 0x35, 0x41,
	0x46, 0x32, 0x33, 0x42, 0x36, 0xa0, 0x00, 0x00,
	0x00, 0x02, 0x01, 0x12, 0x09, 0x00, 0x00, 0x00,
	0xde, 0x00, 0xff, 0xff, 0x01, 0x7d, 0x08, 0x00,
	0x00, 0x00
};

void __fastcall RakHook::SendBuffered(RakNet::RakPeerInterface* instance, PVOID trash, const char *data, RakNet::BitSize_t numberOfBitsToSend, RakNet::PacketPriority priority, RakNet::PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, RakNet::RemoteSystemStruct::ConnectMode connectionMode, RakNet::uint32_t receipt, char a22)
{
	// Gets the packet identifier.
	int identifier = (int)data[0];
	// Writes to the dump file.
	DumpFile << "Sending message ID: 0x" << hex << identifier << endl;
	// Checks the packet identifier.
	if ((identifier == ID_ROBLOX_START_AUTH_THREAD) || (identifier == ID_ROBLOX_AUTH) || (identifier == ID_ROBLOX_INITIAL_SPAWN_NAME))
	{
		// Detatches the hook to prevent recursion.
		pSendBufferedHook->Detatch();
		// Calls the original function.
		instance->SendBuffered(data, numberOfBitsToSend, priority, reliability, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, broadcast, connectionMode, receipt, a22);
		// Attaches the hook.
		pSendBufferedHook->Attach();
	}
	else if (identifier == ID_ROBLOX_UNKNOWN)
	{
		// Detatches the hook to prevent recursion.
		pSendBufferedHook->Detatch();
		// Calls the original function.
		instance->SendBuffered(UnknownMessage, sizeof(UnknownMessage) * 8, priority, reliability, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, broadcast, connectionMode, receipt, a22);
		// Attaches the hook.
		pSendBufferedHook->Attach();
		// Stops execution.
		MessageBoxW(NULL, L"Caught one!", L"Got 'em!", NULL);
	}
}

void __fastcall RakHook::SendBufferedList(RakNet::RakPeerInterface* instance, PVOID trash, const char **data, const int *lengths, const int numParameters, RakNet::PacketPriority priority, RakNet::PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, RakNet::RemoteSystemStruct::ConnectMode connectionMode, uint32_t receipt, char a22)
{
	// Gets the packet identifier.
	int identifier = (int)data[0][0];
	// Writes to the dump file.
	DumpFile << "Sending message list ID: 0x" << hex << identifier << endl;
	// Checks the packet identifier.
	if ((identifier == ID_ROBLOX_SCHEMA_VERSION) || (identifier == ID_ROBLOX_START_AUTH_THREAD) || (identifier == ID_ROBLOX_AUTH) || (identifier == ID_ROBLOX_INITIAL_SPAWN_NAME))
	{
		// Writes to the dump file.
		DumpFile << "Sending message ID: 0x" << hex << (int)data[0][0] << endl;
		// Detatches the hook to prevent recursion.
		pSendBufferedListHook->Detatch();
		// Calls the original function.
		instance->SendBufferedList(data, lengths, numParameters, priority, reliability, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, broadcast, connectionMode, receipt, a22);
		// Attaches the hook.
		pSendBufferedListHook->Attach();
	}
}

RakNet::Packet* __fastcall RakHook::Receive(RakNet::RakPeerInterface* instance, PVOID trash)
{
	// Detatches the hook to prevent recursion.
	pReceiveHook->Detatch();
	// Calls the original function.
	RakNet::Packet* Result = instance->Receive();
	// Attaches the hook.
	pReceiveHook->Attach();

	// Writes to the dump file.
	// DumpFile << "Received: " << to_string((const char*)Result->data, (int)Result->length) << endl;

	// Returns the result.
	return Result;
}

std::string JsonParams = R"({"ClientPort":0,"MachineAddress":"199.229.251.228","ServerPort":49853,"PingUrl":"https://assetgame.roblox.com/Game/ClientPresence.ashx?version=old&PlaceID=876052679&GameID=f9152d4f-adef-43ff-8fa5-3f9d9e7e7e95&UserID=19897681","PingInterval":120,"UserName":"hunter24957","SeleniumTestMode":false,"UserId":19897681,"RobloxLocale":"en_us","GameLocale":"en_us","SuperSafeChat":false,"CharacterAppearance":"https://api.roblox.com/v1.1/avatar-fetch/?placeId=876052679&userId=19897681","ClientTicket":"7/21/2018 10:05:52 AM;MZ7zocYNvnUJ5m2V+PElVgSqIMbOC8Sf5eIeIlK+TkpuD+fTzeIZTaSu7jl3+k76t5A4EWecs99aKE/vVbTb+ZKlFl+WL4/rYwDs7FxEXNjTyz6k0iur6fS3qUukLdsozsD31s2ao15k6+3wuV6egMw79+Rn/3fduXdVjeW1Ni5HwSaqi7eeou5TVwES+YwKHiHT/vE9kmwQhqcGycuGw+5td3B3vhrDfJczdxchbtWToqNYX1cSTpNm3jjXsAdSYfQB+LgQ7i4X/D1dF6FLZHwVIEOkpPtTQsGvcYT9h3y4hUBS3Irc4Z6MOg078f3qK3SJMxeKgqRwLaOA337FmA==;TFdJjrNl8cDmkB8EDhO7eC69JZecBNudKzwVwkhMMb6jkF61jrEX6n8Wp0pNobH9eLZtYfD5MpUrgNZ6Of43f9VGDofTKQwhyBTKniy5iRjziG55MD6qZkdYYR3sBGcn0AApSHgBthf6rAm586NOpDg+02xdE6YSqChHd5lgdoqWDvowfctcstJwFoLC2V8Tv5ZayJaFGJR+ZmP61dGoEH759mLW8T1Od4RM7LKFNOXMEIFRlugjvRnV5KEaGY6F80JBsrc+3EhkQKYRdGBAtik7L55Zf+Rr682p2dXKeW5lNwfePbC5bS7L9sOirdTCQKDqxtOR3nqEAY1qvTadJQ==;2","NewClientTicket":"7/21/2018 10:05:52 AM;MZ7zocYNvnUJ5m2V+PElVgSqIMbOC8Sf5eIeIlK+TkpuD+fTzeIZTaSu7jl3+k76t5A4EWecs99aKE/vVbTb+ZKlFl+WL4/rYwDs7FxEXNjTyz6k0iur6fS3qUukLdsozsD31s2ao15k6+3wuV6egMw79+Rn/3fduXdVjeW1Ni5HwSaqi7eeou5TVwES+YwKHiHT/vE9kmwQhqcGycuGw+5td3B3vhrDfJczdxchbtWToqNYX1cSTpNm3jjXsAdSYfQB+LgQ7i4X/D1dF6FLZHwVIEOkpPtTQsGvcYT9h3y4hUBS3Irc4Z6MOg078f3qK3SJMxeKgqRwLaOA337FmA==;TFdJjrNl8cDmkB8EDhO7eC69JZecBNudKzwVwkhMMb6jkF61jrEX6n8Wp0pNobH9eLZtYfD5MpUrgNZ6Of43f9VGDofTKQwhyBTKniy5iRjziG55MD6qZkdYYR3sBGcn0AApSHgBthf6rAm586NOpDg+02xdE6YSqChHd5lgdoqWDvowfctcstJwFoLC2V8Tv5ZayJaFGJR+ZmP61dGoEH759mLW8T1Od4RM7LKFNOXMEIFRlugjvRnV5KEaGY6F80JBsrc+3EhkQKYRdGBAtik7L55Zf+Rr682p2dXKeW5lNwfePbC5bS7L9sOirdTCQKDqxtOR3nqEAY1qvTadJQ==;2","GameId":"f9152d4f-adef-43ff-8fa5-3f9d9e7e7e95","PlaceId":876052679,"MeasurementUrl":"https://assetgame.roblox.com/Game/ClientPresence.ashx?version=old&PlaceID=876052679&GameID=f9152d4f-adef-43ff-8fa5-3f9d9e7e7e95&UserID=19897681","WaitingForCharacterGuid":"c0b23d89-bb3b-46e6-8be9-cb14c83ff9bf","BaseUrl":"http://assetgame.roblox.com/","ChatStyle":"Classic","VendorId":68,"ScreenShotInfo":"Robber+(Beta)%0d%0aA+FPS+game+by+hunter24957%0d%0aBuilt+in+ROBLOX%2c+the+free+online+building+game.+%0d%0ahttps%3a%2f%2fassetgame.roblox.com%2fgames%2f876052679%2fRobber-Beta%0d%0aMore+about+this+level%3a%0d%0aThe+game+is+in+beta+but+still+needs+enough+polishes+to+be+visually+appealing+and+understandable%2c+also+needs+balancing.+So+you+are+expected+to+experience+a+lot+of+shutdowns+for+experimental+changes%0d%0a%0d%0aTutorial%3a+https%3a%2f%2fwww.youtube.com%2fwatch%3fv%3ddlTrQaQmnXI%0d%0a(Ingame+Tutorial+soon+as+well+as+making+the+UI+less+confusing+and+more+attractive)%0d%0aTwitter%3a+%40DevRolve+%23RBLXRobber%0d%0a%0d%0a%0d%0aA+group+of+people+are+selected+as+robbers+while+the+rest+plays+as+guards.%0d%0a%0d%0aThe+robbers+have+to+do+their+objective+and+escape.%0d%0a%0d%0aWhile+the+guards+have+to+protect+the+objective+by+killing+all+the+robbers+or+waiting+till+dawn%0d%0a%0d%0aThe+guards+can+spot+the+robber+by+using+the+E+key+or+damaging+them+which+alerts+the+SWAT+(i.e.+dead+guards+who+will+respawn+after+a+set+amount+of+time)%0d%0a%0d%0aStarted+as+a+1-week+game+jam+based+on+concepts+by+mightybaseplate+and+now+it%27s+an+official+game","VideoInfo":"<?xml version=\"1.0\"?><entry xmlns=\"http://www.w3.org/2005/Atom\" xmlns:media=\"http://search.yahoo.com/mrss/\" xmlns:yt=\"http://gdata.youtube.com/schemas/2007\"><media:group><media:title type=\"plain\"><![CDATA[Robber (Beta) by ROLVe Community]]></media:title><media:description type=\"plain\"><![CDATA[The game is in beta but still needs enough polishes to be visually appealing and understandable, also needs balancing. So you are expected to experience a lot of shutdowns for experimental changes\\n\\nTutorial: https://www.youtube.com/watch?v=dlTrQaQmnXI\\n(Ingame Tutorial soon as well as making the UI less confusing and more attractive)\\nTwitter: @DevRolve #RBLXRobber\\n\\n\\nA group of people are selected as robbers while the rest plays as guards.\\n\\nThe robbers have to do their objective and escape.\\n\\nWhile the guards have to protect the objective by killing all the robbers or waiting till dawn\\n\\nThe guards can spot the robber by using the E key or damaging them which alerts the SWAT (i.e. dead guards who will respawn after a set amount of time)\\n\\nStarted as a 1-week game jam based on concepts by mightybaseplate and now it&#39;s an official game\\n\\n Visit this place at http://www.roblox.com/games/876052679/Robber-Beta\\n\\nFor more games visit http://www.roblox.com]]></media:description><media:category scheme=\"http://gdata.youtube.com/schemas/2007/categories.cat\">Games</media:category><media:keywords>ROBLOX, video, free game, online virtual world, FPS</media:keywords></media:group></entry>","CreatorId":2613928,"CreatorTypeEnum":"Group","MembershipType":"None","AccountAge":2509,"CookieStoreFirstTimePlayKey":"rbx_evt_ftp","CookieStoreFiveMinutePlayKey":"rbx_evt_fmp","CookieStoreEnabled":true,"IsRobloxPlace":false,"GenerateTeleportJoin":false,"IsUnknownOrUnder13":false,"GameChatType":"AllUsers","SessionId":"{\"SessionId\":\"56c5ae75-9640-4eb9-b25f-4a9f83f1c621\",\"GameId\":\"f9152d4f-adef-43ff-8fa5-3f9d9e7e7e95\",\"PlaceId\":876052679,\"ClientIpAddress\":\"82.43.111.174\",\"PlatformTypeId\":5,\"SessionStarted\":\"2018-07-21T15:05:52.5664762Z\",\"BrowserTrackerId\":15174949569,\"PartyId\":null,\"Age\":28.551459959523935,\"Latitude\":50.7,\"Longitude\":-3.5333,\"CountryId\":2,\"LanguageId\":41}","AnalyticsSessionId":"56c5ae75-9640-4eb9-b25f-4a9f83f1c621","DataCenterId":111,"UniverseId":364078646,"BrowserTrackerId":15174949569,"UsePortraitMode":false,"FollowUserId":0,"characterAppearanceId":19897681,"CountryCode":"GB"})";

int __fastcall RakHook::JoinServer(RBX::PlayerConfigurer * PlayerConfigurer, void * trash, int a2, int * a3, std::string * pJSON, __int64 * a5)
{
	// Writes to the dump file.
	DumpFile << "JSON Params: " << *pJSON << endl;
	
	pJSON = &JsonParams;

	// Detatches the hook to prevent recursion.
	pJoinServer->Detatch();
	// Calls the original function.
	int Result = PlayerConfigurer->JoinServer(a2, a3, pJSON, a5);
	// Attaches the hook.
	pJoinServer->Attach();
	// Returns the result.
	return Result;
}

// hook constructor, get class and hook methods.