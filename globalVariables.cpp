char intstr[5];
int serverSockId, clientSockId;
struct sockaddr_in serverSockAddr,clientSockAddr;
socklen_t clientStorageSize,serverStorageSize;
struct sockaddr_storage serverStorage,clientStorage;
std::string clientIP; 
int status,i;
int BUFFERSIZE=4096;
char messageBuffer[4096];
int bytesRead;
int PORT = 1234;
int DEBUG = 0;
int listenStatus;
bool keepAlive = 1;
std::string rootDir = "/home/cse425user/webfiles";
