package com.qkforex.shell.service;

import com.qkforex.shell.repository.Command;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class CommandService {

    @Autowired
    private Command command;

    public String exec(String[] args)
    {
        return command.exec(args);
    }
}
