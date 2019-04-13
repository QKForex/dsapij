package com.qkforex.rabbitmq.consumer;

import com.qkforex.rabbitmq.conf.RabbitConfig;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;


@Component
public class MsgReceiver {

    @Autowired
    private RabbitTemplate rabbitTemplate;

    @RabbitListener(queues = {RabbitConfig.QUEUE_A})
    public void handleMessage(String message) throws Exception {
        //rabbitTemplate.receive(RabbitConfig.QUEUE_A,30);
        rabbitTemplate.receiveAndConvert(RabbitConfig.QUEUE_A,30);
        // 处理消息
        //String message=new String(RabbitConfig.QUEUE_A.getBytes(),"UTF8");
        System.out.println("MsgReceiver {} handleMessage :"+message);
        //return message;
    }
}

