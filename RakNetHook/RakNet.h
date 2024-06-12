#pragma once
#include <Windows.h>

// Defines various RakNet functions and definitions.
namespace RakNet
{
	// Defines the RakNet compiler types.
	typedef __int8 int8_t;
	typedef __int16 int16_t;
	typedef __int32 int32_t;
	typedef __int64 int64_t;
	typedef unsigned __int8 uint8_t;
	typedef unsigned __int16 uint16_t;
	typedef unsigned __int32 uint32_t;
	typedef unsigned __int64 uint64_t;

	// Defines some RakNet types.
	typedef uint32_t sa_family_t;
	typedef uint32_t TimeMS;
	typedef uint32_t BitSize_t;
	typedef unsigned short SystemIndex;

	typedef void SocketDescriptor;
	typedef void BitStream;
	// typedef void SystemAddress;
	typedef void RakNetSocket2;

	namespace RemoteSystemStruct {
		enum ConnectMode
		{
			NO_ACTION,
			DISCONNECT_ASAP,
			DISCONNECT_ASAP_SILENTLY,
			DISCONNECT_ON_NO_ACK,
			REQUESTED_CONNECTION,
			HANDLING_CONNECTION_REQUEST,
			UNVERIFIED_SENDER,
			CONNECTED
		};
	}

	enum StartupResult
	{
		RAKNET_STARTED,
		RAKNET_ALREADY_STARTED,
		INVALID_SOCKET_DESCRIPTORS,
		INVALID_MAX_CONNECTIONS,
		SOCKET_FAMILY_NOT_SUPPORTED,
		SOCKET_PORT_ALREADY_IN_USE,
		SOCKET_FAILED_TO_BIND,
		SOCKET_FAILED_TEST_SEND,
		PORT_CANNOT_BE_ZERO,
		FAILED_TO_CREATE_NETWORK_THREAD,
		COULD_NOT_GENERATE_GUID,
		STARTUP_OTHER_FAILURE
	};

	enum ConnectionAttemptResult
	{
		CONNECTION_ATTEMPT_STARTED,
		INVALID_PARAMETER,
		CANNOT_RESOLVE_DOMAIN_NAME,
		ALREADY_CONNECTED_TO_ENDPOINT,
		CONNECTION_ATTEMPT_ALREADY_IN_PROGRESS,
		SECURITY_INITIALIZATION_FAILED
	};

	enum PacketPriority {
		IMMEDIATE_PRIORITY,
		HIGH_PRIORITY,
		MEDIUM_PRIORITY,
		LOW_PRIORITY,
		NUMBER_OF_PRIORITIES
	};

	enum PacketReliability {
		UNRELIABLE,
		UNRELIABLE_SEQUENCED,
		RELIABLE,
		RELIABLE_ORDERED,
		RELIABLE_SEQUENCED,
		UNRELIABLE_WITH_ACK_RECEIPT,
		RELIABLE_WITH_ACK_RECEIPT,
		RELIABLE_ORDERED_WITH_ACK_RECEIPT,
		NUMBER_OF_RELIABILITIES
	};

	enum PublicKeyMode
	{
		/// The connection is insecure. You can also just pass 0 for the pointer to PublicKey in RakPeerInterface::Connect()
		PKM_INSECURE_CONNECTION,

		/// Accept whatever public key the server gives us. This is vulnerable to man in the middle, but does not require
		/// distribution of the public key in advance of connecting.
		PKM_ACCEPT_ANY_PUBLIC_KEY,

		/// Use a known remote server public key. PublicKey::remoteServerPublicKey must be non-zero.
		/// This is the recommended mode for secure connections.
		PKM_USE_KNOWN_PUBLIC_KEY,

		/// Use a known remote server public key AND provide a public key for the connecting client.
		/// PublicKey::remoteServerPublicKey, myPublicKey and myPrivateKey must be all be non-zero.
		/// The server must cooperate for this mode to work.
		/// I recommend not using this mode except for server-to-server communication as it significantly increases the CPU requirements during connections for both sides.
		/// Furthermore, when it is used, a connection password should be used as well to avoid DoS attacks.
		PKM_USE_TWO_WAY_AUTHENTICATION
	};

	/// Passed to RakPeerInterface::Connect()
	struct PublicKey
	{
		/// How to interpret the public key, see above
		PublicKeyMode publicKeyMode;

		/// Pointer to a public key of length cat::EasyHandshake::PUBLIC_KEY_BYTES. See the Encryption sample.
		char *remoteServerPublicKey;

		/// (Optional) Pointer to a public key of length cat::EasyHandshake::PUBLIC_KEY_BYTES
		char *myPublicKey;

		/// (Optional) Pointer to a private key of length cat::EasyHandshake::PRIVATE_KEY_BYTES
		char *myPrivateKey;
	};

	struct AddressOrGUID
	{
		int a[11];
	};

	struct SystemAddress
	{
		/// SystemAddress, with RAKNET_SUPPORT_IPV6 defined, holds both an sockaddr_in6 and a sockaddr_in
		union// In6OrIn4
		{
#if RAKNET_SUPPORT_IPV6==1
			struct sockaddr_storage sa_stor;
			sockaddr_in6 addr6;
#endif

			sockaddr_in addr4;
		} address;

		/// This is not used internally, but holds a copy of the port held in the address union, so for debugging it's easier to check what port is being held
		unsigned short debugPort;

		/// \internal Used internally for fast lookup. Optional (use -1 to do regular lookup). Don't transmit this.
		SystemIndex systemIndex;
	};

	struct RakNetGUID
	{
		//	uint32_t g[6];
		uint64_t g;
		// Used internally for fast lookup. Optional (use -1 to do regular lookup). Don't transmit this.
		SystemIndex systemIndex;
	};

	/// This represents a user message from another system.
	struct Packet
	{
		/// The system that send this packet.
		SystemAddress systemAddress;

		/// A unique identifier for the system that sent this packet, regardless of IP address (internal / external / remote system)
		/// Only valid once a connection has been established (ID_CONNECTION_REQUEST_ACCEPTED, or ID_NEW_INCOMING_CONNECTION)
		/// Until that time, will be UNASSIGNED_RAKNET_GUID
		RakNetGUID guid;

		/// The length of the data in bytes
		unsigned int length;

		/// The length of the data in bits
		BitSize_t bitSize;

		/// The data from the sender
		unsigned char* data;

		/// @internal
		/// Indicates whether to delete the data, or to simply delete the packet.
		bool deleteData;

		/// @internal
		/// If true, this message is meant for the user, not for the plugins, so do not process it through plugins
		bool wasGeneratedLocally;
	};

	// Defines the RakPeer send buffered method.
	// typedef void __fastcall SendBuffered(RakPeerInterface* instance, PVOID trash, const char *data, BitSize_t numberOfBitsToSend, PacketPriority priority, PacketReliability reliability, char orderingChannel, const AddressOrGUID systemIdentifier, bool broadcast, RemoteSystemStruct::ConnectMode connectionMode, uint32_t receipt);

	// Defines the RakPeerInterface class.
	// This class is used by RakNet to interface with a server or clients.
	class RakPeerInterface
	{
	public:

		void SendBuffered(const char *data, BitSize_t numberOfBitsToSend, PacketPriority priority, PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, RemoteSystemStruct::ConnectMode connectionMode, uint32_t receipt, char a22);
		void SendBufferedList(const char **data, const int *lengths, const int numParameters, PacketPriority priority, PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, RemoteSystemStruct::ConnectMode connectionMode, uint32_t receipt, char a22);

		// Defines the functions.
		// They seem to be in a weird order (fix this later).
		virtual ~RakPeerInterface();
		virtual StartupResult Startup(unsigned int maxConnections, SocketDescriptor *socketDescriptors, unsigned socketDescriptorCount, int threadPriority);
		virtual bool InitializeSecurity(const char *publicKey, const char *privateKey, bool bRequireClientKey = false);
		virtual void DisableSecurity(void);
		virtual void AddToSecurityExceptionList(const char *ip);
		virtual void RemoveFromSecurityExceptionList(const char *ip);
		virtual bool IsInSecurityExceptionList(const char *ip);
		virtual void SetMaximumIncomingConnections(unsigned short numberAllowed);
		virtual unsigned int GetMaximumIncomingConnections(void);
		virtual unsigned short NumberOfConnections(void);
		virtual void SetIncomingPassword(const char* passwordData, int passwordDataLength);
		virtual void GetIncomingPassword(char* passwordData, int *passwordDataLength);
		virtual ConnectionAttemptResult Connect(const char* host, unsigned short remotePort, const char *passwordData, int passwordDataLength, PublicKey *publicKey = 0, unsigned connectionSocketIndex = 0, unsigned sendConnectionAttemptCount = 12, unsigned timeBetweenSendConnectionAttemptsMS = 500, RakNet::TimeMS timeoutTime = 0);
		virtual ConnectionAttemptResult ConnectWithSocket(const char* host, unsigned short remotePort, const char *passwordData, int passwordDataLength, RakNetSocket2* socket, PublicKey *publicKey = 0, unsigned sendConnectionAttemptCount = 12, unsigned timeBetweenSendConnectionAttemptsMS = 500, RakNet::TimeMS timeoutTime = 0);
		virtual void Shutdown(unsigned int blockDuration, unsigned char orderingChannel = 0, PacketPriority disconnectionNotificationPriority = LOW_PRIORITY);
		// virtual bool IsActive(void);
		virtual bool GetConnectionList(SystemAddress *remoteSystems, unsigned short *numberOfSystems);
		virtual uint32_t GetNextSendReceipt(void);
		virtual uint32_t IncrementNextSendReceipt(void);
		virtual uint32_t Send(const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel, const AddressOrGUID systemIdentifier, bool broadcast, uint32_t forceReceiptNumber = 0);
		virtual void SendLoopback(const char *data, const int length);
		virtual uint32_t Send(const RakNet::BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, const AddressOrGUID systemIdentifier, bool broadcast, uint32_t forceReceiptNumber = 0);
		virtual uint32_t SendList(const char **data, const int *lengths, const int numParameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, const AddressOrGUID systemIdentifier, bool broadcast, uint32_t forceReceiptNumber = 0);
		virtual bool IsActive(void);
		virtual Packet* Receive(void);
		virtual void DeallocatePacket(Packet *packet);
		virtual unsigned int GetMaximumNumberOfPeers(void);
	};

	// Defines the layout of the RakNet peer virtual functions.
	class RakPeer
	{
	public:
		// Defines each function in the vftable.
		PVOID RakPeerInterface;
		PVOID Startup;
		PVOID InitializeSecurity;
		PVOID DisableSecurity;
		PVOID AddToSecurityExceptionList;
		PVOID RemoveFromSecurityExceptionList;
		PVOID IsInSecurityExceptionList;
		PVOID SetMaximumIncomingConnections;
		PVOID GetMaximumIncomingConnections;
		PVOID NumberOfConnections;
		PVOID SetIncomingPassword;
		PVOID GetIncomingPassword;
		PVOID Connect;
		PVOID ConnectWithSocket;
		PVOID Shutdown;
		PVOID IsActive;
		PVOID GetConnectionList;
		PVOID GetNextSendReceipt;
		PVOID IncrementNextSendReceipt;
		PVOID Send;
		PVOID SendLoopback;
		PVOID SendBitstream;
		PVOID SendList;
		PVOID Receive;
		PVOID DeallocatePacket;
		PVOID GetMaximumNumberOfPeers;

		// Gets the RakNet peer class virtual functions.
		static RakPeer* Get();

		// Gets the RakPeer send buffered method.
		static PVOID GetSendBuffered();

		// Gets the RakPeer send buffered list method.
		static PVOID GetSendBufferedList();
	};
}