package com.qkforex.dsapij.controller;


import com.qkforex.dsapij.service.DsapiService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.HashSet;

@Api(description = "DataStage Api ")
@RestController
@RequestMapping(value="/dsapi",method = {RequestMethod.GET})
public class DsapiController {

    @Autowired
    private DsapiService dsapiservice;

    @ApiOperation(value = "show all projects",notes = "show all projects")
    @RequestMapping(value = "/projects",method = RequestMethod.GET)
    @ResponseBody
    public HashSet<String> getAllProjects()
    {
        HashSet<String> projects=dsapiservice.getAllProjects();
        //System.out.println(projects);
        return projects;
    }

    @ApiOperation(value = "show all jobs in default projects",notes = "show all jobs in default projects")
    @RequestMapping(value = "/jobs",method  =  RequestMethod.GET)
    @ResponseBody
    public HashSet<String> getAllJobs()
    {
        HashSet<String> jobs=dsapiservice.getAllJobs(null);
        return jobs;
    }

    @ApiOperation(value="show all jobs in the project  ",notes = "show all jobs in the project  ")
    @RequestMapping(value = "/{ProJectName}/jobs",method  =  RequestMethod.GET)
    @ResponseBody
    public HashSet<String> getAllJobs(@PathVariable("ProJectName") String ProJectName)
    {
        HashSet<String> jobs=dsapiservice.getAllJobs(ProJectName.trim());
        return jobs;
    }

    @ApiOperation(value="show job logdetail ",notes = "show job log detail")
    @RequestMapping(value = "/log/{ProjectName}/{JobName}",method  =  RequestMethod.GET)
    @ResponseBody
    public String getJobLog(@PathVariable("ProjectName") String ProjectName,@PathVariable("JobName") String JobName)
    {
        String log=dsapiservice.getJobLog(ProjectName.trim(),JobName.trim());
        return log;
    }

    @ApiOperation(value = "run a job and waiting it finished then return the job status",notes = "run a job and waiting it finished then return the job status")
    @RequestMapping(value = "/runwait/{ProjectName}/{JobName}",method  =  RequestMethod.GET)
    @ResponseBody
    public String runJobWait(@PathVariable("ProjectName") String ProjectName,@PathVariable("JobName") String JobName)
    {
        String status=dsapiservice.runJob(ProjectName.trim(),JobName.trim(),true);
        return status;
    }

    @ApiOperation(value="run a job in daemon mode then return jobstatus",notes="run a job in daemon mode then return jobstatus")
    @RequestMapping(value = "/rundaemon/{ProjectName}/{JobName}",method  =  RequestMethod.GET)
    @ResponseBody
    public String runJobDaemon(@PathVariable("ProjectName") String ProjectName,@PathVariable("JobName") String JobName)
    {
        //msgProducerService.sendMSG("job "+JobName+" started");
        String status=dsapiservice.runJob(ProjectName.trim(),JobName.trim(),false);
        //msgConsumerSrvice.process("job "+JobName+" finished");
        return status;
    }

    @ApiOperation(value="show job status",notes="show job status")
    @RequestMapping(value = "/status/{ProjectName}/{JobName}",method  =  RequestMethod.GET)
    @ResponseBody
    public String getJobStatus(@PathVariable("ProjectName") String ProjectName,@PathVariable("JobName") String JobName)
    {
        String status=dsapiservice.getJobStatus(ProjectName.trim(),JobName.trim());
        return status;
    }

    @ApiOperation(value="show job ran elapsed ",notes="show job ran elapsed")
    @RequestMapping(value = "/elapsed/{ProjectName}/{JobName}",method  =  RequestMethod.GET)
    @ResponseBody
    public String getJobElapsed(@PathVariable("ProjectName") String ProjectName,@PathVariable("JobName") String JobName)
    {
        String status=dsapiservice.getJobElapsed(ProjectName.trim(),JobName.trim());
        return status;
    }
}
