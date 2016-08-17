void handleGetRequest(HttpRequest request)
{
	if(DEBUG) 
		printf("Handling GET Request\n");
	std::string resource =request.RequestedResource();
	if(resource == "/") resource = "/index.html";
	std::string path = rootDir+resource;
	FILE *file = fopen(path.c_str(),"r");
	std::string mimeType = getMimeType(path);
	if(file!=NULL)
	{
		handle200(mimeType,getFileLength(path),file);
	}
	else
	{
		handle404();
	}
	fclose(file);
}

