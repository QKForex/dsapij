package com.qkforex.rabbitmq.conf;


import com.rabbitmq.client.Channel;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.core.*;
import org.springframework.amqp.rabbit.connection.ConnectionFactory;

import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.amqp.rabbit.listener.SimpleMessageListenerContainer;
import org.springframework.amqp.rabbit.listener.api.ChannelAwareMessageListener;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;


@Configuration
public class RabbitConfig {

    private final Logger logger = LoggerFactory.getLogger(this.getClass());

    @Value("${spring.rabbitmq.host}")
    private String host;

    @Value("${spring.rabbitmq.port}")
    private int port;

    @Value("${spring.rabbitmq.username}")
    private String username;

    @Value("${spring.rabbitmq.password}")
    private String password;

    @Value("${spring.rabbitmq.virtual-host}")
    private String virtual_host;


    public static final String EXCHANGE_A = "my-mq-exchange_A";

    public static final String QUEUE_A = "QUEUE_A";

    public static final String ROUTINGKEY_A = "spring-boot-routingKey_A";

    @Autowired
    private ConnectionFactory connectionFactory;

    @Bean
    public MsgSendConfirmCallBack msgSendConfirmCallBack(){
        return new MsgSendConfirmCallBack();
    }
    @Bean
    public MsgSendReturnCallback msgSendReturnCallback(){
        return new MsgSendReturnCallback();
    }
   @Bean
   public RabbitTemplate rabbitTemplate() {
       RabbitTemplate template = new RabbitTemplate(connectionFactory);
       /**若使用confirm-callback或return-callback，
        * 必须要配置publisherConfirms或publisherReturns为true
        * 每个rabbitTemplate只能有一个confirm-callback和return-callback
        */
       //template.setConfirmCallback(msgSendConfirmCallBack());
       //template.setReturnCallback(msgSendReturnCallback());
       /**
        * 使用return-callback时必须设置mandatory为true，或者在配置中设置mandatory-expression的值为true，
        * 可针对每次请求的消息去确定’mandatory’的boolean值，
        * 只能在提供’return -callback’时使用，与mandatory互斥
        */
       //  template.setMandatory(true);
       template.setReturnCallback(msgSendReturnCallback());
       template.setMandatory(true);
       return template;
   }
    /**
     * 针对消费者配置
     * 1. 设置交换机类型
     * 2. 将队列绑定到交换机
     * FanoutExchange: 将消息分发到所有的绑定队列，无routingkey的概念
     * HeadersExchange ：通过添加属性key-value匹配
     * DirectExchange:按照routingkey分发到指定队列
     * TopicExchange:多关键字匹配
     */
    @Bean
    public DirectExchange defaultExchange() {
        return new DirectExchange(EXCHANGE_A,true,false);
    }

    /**
     * 获取队列A
     *
     * @return
     */
    @Bean
    public Queue queueA() {
        return new Queue(QUEUE_A, true,false,false); //队列持久
    }

    @Bean
    public Binding binding() {

        return BindingBuilder.bind(queueA()).to(defaultExchange()).with(RabbitConfig.ROUTINGKEY_A);
    }


  /*  @Bean
    public SimpleMessageListenerContainer messageContainer() {
        //加载处理消息A的队列
        SimpleMessageListenerContainer container = new SimpleMessageListenerContainer(connectionFactory);
        //设置接收多个队列里面的消息，这里设置接收队列A
        //假如想一个消费者处理多个队列里面的信息可以如下设置：
        //container.setQueues(queueA(),queueB(),queueC());
        container.setQueues(queueA());
        container.setExposeListenerChannel(true);
        //设置最大的并发的消费者数量
        container.setMaxConcurrentConsumers(10);
        //最小的并发消费者的数量
        container.setConcurrentConsumers(1);
        //设置确认模式手工确认
        container.setAcknowledgeMode(AcknowledgeMode.MANUAL);
        container.setMessageListener(new ChannelAwareMessageListener() {
            @Override
            public void onMessage(Message message, Channel channel) throws Exception {
                *//**通过basic.qos方法设置prefetch_count=1，这样RabbitMQ就会使得每个Consumer在同一个时间点最多处理一个Message，
                 换句话说,在接收到该Consumer的ack前,它不会将新的Message分发给它 *//*
                channel.basicQos(1);
                byte[] body = message.getBody();
                logger.info("接收处理队列A当中的消息:" + new String(body));
                *//**为了保证永远不会丢失消息，RabbitMQ支持消息应答机制。
                 当消费者接收到消息并完成任务后会往RabbitMQ服务器发送一条确认的命令，然后RabbitMQ才会将消息删除。*//*
                channel.basicAck(message.getMessageProperties().getDeliveryTag(), false);
            }
        });
        return container;
    }*/

}