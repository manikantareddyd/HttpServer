//Not for recreational purposes
void *intTostr(int a);
int scan(char *input, char *output, int start, int max);
int writeToSocket(char *messageBuffer, FILE *writeSocket);

void logToFile(std::string text)
{
	std::mutex m;
	m.lock();
	m.unlock();
}

char easytolower(char in){
  if(in<='Z' && in>='A')
    return in-('Z'-'z');
  return in;
} 


std::string getConnection(HttpRequest request)
{
	std::string connection;
    if(request["Connection"] == "" && request["connection"] == "")
      connection = "keep-alive";
    else
    {
      if(request["connection"]=="")
	  {
		  connection = request["Connection"];
		  std::transform(connection.begin(), connection.end(), connection.begin(), easytolower);
	  } 
      else 
	  {
		  connection = request["connection"];
		  std::transform(connection.begin(), connection.end(), connection.begin(), easytolower);
	  }
    }
	connection.resize (connection.size () - 1);
	return connection;
}

std::string getMimeType(std::string path)
{
	std::string ext = path.substr(path.find_last_of(".") + 1);
	std::string mimeType;
	if(ext == "html")
		mimeType = "text/html";
	else if(ext == "jpg" or ext == "jpeg")
		mimeType = "image/jpeg";
	else if(ext == "txt")
		mimeType = "text/plain";
	else if(ext == "pdf")
		mimeType = "Application/pdf";
	else if(ext == "gif")
		mimeType = "image/gif";
	else
		mimeType = "unknown";
	return mimeType; 
}

int getFileLength(std::string filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}


int getExtension(char *input, char *output, int max)
{
	int in_position = 0;
	int appended_position = 0;
	int i = 0;
	int count = 0;

	for ( ; i < strlen(input); i ++ )
	{		
		if ( in_position == 1 )
		{
			if(count < max)
			{
				output[appended_position] = input[i];
				appended_position +=1;
				count++;
			}
		}

		if ( input[i] == '.' )
			in_position = 1;

	}

	output[appended_position+1] = '\0';

	if ( strlen(output) > 0 )
		return 1;

	return -1;
}

void sigintHandler(int sig_num)
{
	//Helps to keep ports from being blocked when we close the server :P
	close(listenStatus);
	close(clientSockId);
	close(serverSockId);
	exit(0);
}



void *intTostr(int a)
{
	memset(intstr,0,4);
	int i;
	for(i=0;i<4;i++)
	{
		intstr[3-i] = '0' + a%10;
		a = a/10;
	}
	intstr[4] = 0;
}
