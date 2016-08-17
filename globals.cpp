char intstr[5];
int serverSockId, clientSockId;

struct sockaddr_in serverSockAddr,clientSocAddr;
int status,i;
char messageBuffer[4096];
int bytesRead;
struct sockaddr_storage serverStorage;
socklen_t serverStorageSize;
int PORT;
int DEBUG = 1;
int listenStatus;
bool keepAlive;
