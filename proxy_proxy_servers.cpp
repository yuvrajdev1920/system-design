#include<bits/stdc++.h>
using namespace std;


class Server{
    private:
    string ip;
    string response="";
    public:
    string url;
    Server(string url,string ip, string response){
        cout<<"Creating Server..."<<endl;
        this->ip=ip;
        this->url=url;
        this->response=response;
    }
    string sendResponse(){
        return response;
    }
};

class ProxyServer{
    public:
    string proxy_ip;
    string proxy_response;
    Server *server;
    ProxyServer(){}
    ProxyServer(string proxy_ip,Server *server){
        this->proxy_ip=proxy_ip;
        this->server=server;
    }
    string sendResponse(){
        return server->sendResponse();
    }
};


class DNSServer{
    private:
    unordered_map<string,string> dns;
    public:
    void setMapping(string url,string ip){
        dns[url]=ip;
    }
    string resolve(string url)
    {
        return dns[url];
    }
};

class Internet{
    private:
    unordered_map<string,ProxyServer> ServerMap;
    public:
    void setMapping(string ip, ProxyServer proxy_server){
        ServerMap[ip]=proxy_server;
    }
    ProxyServer getServer(string ip){
        return ServerMap[ip];
    }
};

class Client{
    public:
    string request(string url,DNSServer dns_server,Internet internet){
        string server_ip=dns_server.resolve(url);
        return internet.getServer(server_ip).sendResponse();
    }
};

int main(){
    Internet internet;
    DNSServer dns_server;

    Server google("www.google.com","42.65.12.67","This is google.com");
    ProxyServer google_proxy("67.12.13.1",&google);
    internet.setMapping(google_proxy.proxy_ip,google_proxy);
    dns_server.setMapping(google.url,google_proxy.proxy_ip);

    Client client;
    cout<<client.request("www.google.com",dns_server,internet)<<endl;
    return 0;
}