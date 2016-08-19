void handleGetRequest(HttpRequest request)
{
	if(DEBUG) 
		printf("Handling GET Request\n");
	std::string resource =request.RequestedResource();
	if(resource == "/") resource = "/index.html";
	std::string path = rootDir+resource;
	std::string connection;
    if(request["Connection"] == "" && request["connection"] == "")
      connection = "keep-alive";
    else
    {
      if(request["connection"]=="") connection = request["Connection"];
      else connection = request["connection"];
    }
	FILE *file = fopen(path.c_str(),"r");
	std::string mimeType = getMimeType(path);
	if(DEBUG)
	{
		cout<<path<<endl;
		cout<<file<<endl;
		cout<<connection<<endl;
	}
		
	if(file!=NULL)
	{
		handle200(mimeType,getFileLength(path),file,connection);
	}
	else
	{
		handle404(connection);
	}
	fclose(file);
}

