package com.qkforex.shell.repository;


import org.springframework.stereotype.Repository;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

@Repository
public class Command implements CommandRepository {
    @Override
    public String exec(String[] args) {

        String os=System.getProperty("os.name");
        //System.out.println(os);
        List<String> cmds = new ArrayList<String>();
        if (os.toLowerCase().startsWith("win"))
        {
            cmds.add("cmd.exe ");
            cmds.add("/c");
        }
        if (os.toLowerCase().startsWith("linux")) {
            cmds.add("/bin/bash");
            cmds.add("-c");
        }
        for (String arg:args)
            cmds.add(arg);
        ProcessBuilder pb=new ProcessBuilder(cmds);
        StringBuffer valueString=new StringBuffer();
        try {
            Process p = pb.start();
            BufferedInputStream in=new BufferedInputStream(p.getInputStream());
            BufferedReader br=new BufferedReader(new InputStreamReader(in));
            String value = null;
            while((value=br.readLine())!=null) {
                valueString.append(value+System.lineSeparator());
                //System.out.println(valueString);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
        return valueString.toString();
    }

    public static void main(String[] args) {
        Command cmd=new Command();
        System.out.println(cmd.exec(new String[]{"ls /"}));
    }
}
