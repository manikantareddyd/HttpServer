void handlePostRequest(HttpRequest request)
{
    std::string connection = getConnection(request);
    if(DEBUG) 
		printf("Handling POST Request\n");
    handle501(connection);
}
