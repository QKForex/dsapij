package com.qkforex.dsapij.conf;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Component
public class DServer {

    @Value("${DServer.domain}")
    private String domain;

    @Value("${DServer.user}")
    private String user;

    @Value("${DServer.password}")
    private String password;

    @Value("${DServer.server}")
    private String server;

    @Value("${DServer.defaultproject}")
    private String defaultproject;

    public String getDomain() {
        return domain;
    }

    public void setDomain(String domain) {
        this.domain = domain;
    }

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getServer() {
        return server;
    }

    public void setServer(String server) {
        this.server = server;
    }

    public String getDefaultproject() {
        return defaultproject;
    }

    public void setDefaultproject(String defaultproject) {
        this.defaultproject = defaultproject;
    }
}
