char intstr[5];
int serverSockId, clientSockId;
struct sockaddr_in serverSockAddr,clientSocAddr;
int status,i;
char messageBuffer[4096];
int bytesRead;
struct sockaddr_storage serverStorage;
int serverStorageSize;
int PORT;

