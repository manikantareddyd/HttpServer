void handleHeadRequest(HttpRequest request)
{
    std::string connection = getConnection(request);
    if(DEBUG) 
		printf("Handling HEAD Request\n");
    handle501(connection);
}
