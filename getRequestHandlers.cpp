void handleGetRequest(HttpRequest request)
{
	if(DEBUG) 
		printf("Handling GET Request\n");
	std::string resource =request.RequestedResource();
	if(resource[resource.length()-1] == '/') resource = resource + "index.html";
	std::string path = rootDir+resource;
	std::string connection = getConnection(request);
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

