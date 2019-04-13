package com.qkforex.dsapij.service;

import com.qkforex.dsapij.conf.DServer;
import com.qkforex.dsapij.vmdsapi.Dao.DsapiDao;
import com.qkforex.dsapij.vmdsapi.Repository.DsapiRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.HashSet;

@Service
public class DsapiService {

    @Autowired
    private DServer dserver;

    public HashSet<String> getAllProjects()
    {
        //System.out.println(dserver);
        //System.out.println("here is projectname "+dserver.defaultproject);
//        DsapiDao api= new DsapiDao(dserver.domain, dserver.user, dserver.password, dserver.server, dserver.defaultproject);
        DsapiDao api = new DsapiDao(dserver.getDomain(), dserver.getUser(), dserver.getPassword(), dserver.getServer(), dserver.getDefaultproject());
        //System.out.println(dsapi1);

        //System.out.println("api is ");
        return api.DSGetProjectlist();
    }

   public HashSet<String> getAllJobs(String ProjectName)
    {
        //System.out.println("chuan ru de gongcheng name "+ProjectName);
        DsapiDao api=null;
        if(ProjectName==null|| "".equals(ProjectName)){
            //System.out.println("here");
        api=new DsapiDao(dserver.getDomain(), dserver.getUser(), dserver.getPassword(), dserver.getServer(), dserver.getDefaultproject());
        return api.DSGetJoblist(dserver.getDefaultproject());}
        else{
            //System.out.println("now is here ");
            api=new DsapiDao(dserver.getDomain(), dserver.getUser(), dserver.getPassword(), dserver.getServer(), ProjectName);
            return api.DSGetJoblist(ProjectName);
        }
    }

    public String getJobLog(String ProjectName,String JobName)
    {
        DsapiDao api=new DsapiDao(dserver.getDomain(), dserver.getUser(), dserver.getPassword(), dserver.getServer(),ProjectName);
        //DsapiRepository.DSPROJECT project=api.DSOpenProject(ProjectName);
        DsapiRepository.DSJOB job=api.DSOpenJob(ProjectName,JobName);
        String log=api.DSGetJobLog(job);
        api.DSLockJob(job);
        api.DSUlockJob(job);
        api.DSCloseJob(job);
        return log;
    }

    public String runJob(String ProjectName,String JobName,boolean wait)
    {
        DsapiDao api=new DsapiDao(dserver.getDomain(), dserver.getUser(), dserver.getPassword(), dserver.getServer(),ProjectName);
        //DsapiRepository.DSPROJECT project=api.DSOpenProject(ProjectName);
        DsapiRepository.DSJOB job=api.DSOpenJob(ProjectName,JobName);

        //MsgProducer msgProducer=new MsgProducer(RabbitTemplate );
        api.DSRunJob(job,wait);
        //msgProducer.sendMsg("");
        //api.DSCloseJob(job);
        String Status=api.DSGetJobStatus(job);
        return Status;
    }

    public String getJobStatus(String ProjectName,String JobName)
    {
        DsapiDao api=new DsapiDao(dserver.getDomain(), dserver.getUser(), dserver.getPassword(), dserver.getServer(),ProjectName);
        //System.out.println(api);
        //DsapiRepository.DSPROJECT project=api.DSOpenProject(ProjectName);
        DsapiRepository.DSJOB job=api.DSOpenJob(ProjectName,JobName);
        String Status=api.DSGetJobStatus(job);
        return Status;
    }

    public String getJobElapsed(String ProjectName,String JobName)
    {
        DsapiDao api=new DsapiDao(dserver.getDomain(), dserver.getUser(), dserver.getPassword(), dserver.getServer(),ProjectName);
        DsapiRepository.DSJOB job=api.DSOpenJob(ProjectName,JobName);
        String elapsed=api.DSGetJobElapsed(job);
        return elapsed;
    }
}
