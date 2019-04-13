package com.qkforex.dsapij;

import com.qkforex.dsapij.controller.DsapiController;
import com.qkforex.rabbitmq.controller.MsgController;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.autoconfigure.SpringBootApplication;


@EnableAutoConfiguration
@SpringBootApplication(scanBasePackages = "com.qkforex.shell",exclude = {MsgController.class,DsapiController.class})
public class DsapijApplication {
    public static void main(String[] args) {
        SpringApplication.run(DsapijApplication.class, args);
    }
}
