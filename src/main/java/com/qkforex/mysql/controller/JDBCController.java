package com.qkforex.mysql.controller;

import com.qkforex.mysql.model.Test;
import com.qkforex.mysql.repository.JDBCRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping(value = "/jdbc")
public class JDBCController {

    @Autowired
    private JDBCRepository jdbcRepository;

    @GetMapping(value="/{id}")
    public Test testList(@PathVariable("id") Integer id){
        return jdbcRepository.getTest(id);
    }

    @PostMapping(value="/add")
    public void testAdd(@RequestParam("id")Integer id,@RequestParam("age")Integer age,@RequestParam("name")String name){
        jdbcRepository.createTest(id,age,name);
    }

    @PutMapping(value="/{id}")
    public void testUpdate(@PathVariable("id") Integer id,@RequestParam("age") Integer age,@RequestParam("name")String name){
        jdbcRepository.updateTest(id,age,name);
    }

    @DeleteMapping(value="/{id}")
    public void testDelete(@PathVariable("id") Integer id){
        jdbcRepository.deleteTest(id);
    }

}