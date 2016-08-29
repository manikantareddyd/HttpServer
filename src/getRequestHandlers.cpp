void handleGetRequest(HttpRequest request)
{
	
	if(DEBUG) 
		printf("Handling GET Request\n");
	std::string resource =request.RequestedResource();
	if(resource[resource.length()-1] == '/') 
		resource = resource + "index.html";
	std::string path = rootDir+resource;
	if(DEBUG) cout<<"Request Path: "<<path<<endl;
	std::string connection = getConnection(request);
	FILE *file = fopen(path.c_str(),"r");
	std::string mimeType = getMimeType(path);
	
	struct stat statbuf;
	stat((char *)path.c_str(), &statbuf);
	if(S_ISDIR(statbuf.st_mode))
    {
		handle501(connection,resource);
		return;
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

