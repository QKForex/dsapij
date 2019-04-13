package com.qkforex.rabbitmq.controller;

import com.qkforex.rabbitmq.consumer.MsgReceiver;
import com.qkforex.rabbitmq.producer.MsgProducer;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.UUID;

@RestController
@RequestMapping(value="/msg",method = {RequestMethod.GET,RequestMethod.POST})
public class MsgController {
    @Autowired
    private MsgProducer msgProducer;

    @Autowired
    private MsgReceiver msgReceiver;

    @RequestMapping(value="/send",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    public String send(@RequestParam("message") String  message){
        String uuid = UUID.randomUUID().toString();
        msgProducer.send(uuid,message);
        return uuid;
    }

/*    @RequestMapping(value="/get",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    public String receive(){
        String message="";
           try {
               message=msgReceiver.handleMessage();
           }catch(Exception e){e.printStackTrace();}
       return message;
    }*/
}