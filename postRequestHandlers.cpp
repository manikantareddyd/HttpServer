void handlePostRequest(HttpRequest request)
{
    std::string connection;
    if(request["Connection"] == "" && request["connection"] == "")
      connection = "keep-alive";
    else
    {
      if(request["connection"]=="") connection = request["Connection"];
      else connection = request["connection"];
    }
    if(DEBUG) 
		printf("Handling POST Request\n");
    handle501(connection);
}
