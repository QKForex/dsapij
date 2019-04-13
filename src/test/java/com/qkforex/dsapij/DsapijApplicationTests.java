package com.qkforex.dsapij;

import org.junit.runner.RunWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.mock.web.MockServletContext;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;

import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.get;

@RunWith(SpringJUnit4ClassRunner.class)
@SpringBootTest(classes = MockServletContext.class)
@WebAppConfiguration
public class DsapijApplicationTests {

    private MockMvc mvc;

  /*  @Before
    public void setUp()throws Exception
    {
        mvc= MockMvcBuilders.standaloneSetup(new DsapiController()).build();
    }

    @Test
    public void contextLoads() throws  Exception {
        RequestBuilder request=null;
        request=get("/dsapi/jobs");
        mvc.perform(request).andExpect(status().isOk()).andExpect(content().string(equalTo("[\n" +
                "  \"DRSToBI_OffloadJob_3\",\n" +
                "  \"DRSToDRS\",\n" +
                "  \"S3ToBI_OffloadJob_1\",\n" +
                "  \"S3SchemaFileCreator\",\n" +
                "  \"S3ToDRS\",\n" +
                "  \"DRSToBI_OffloadJob_2\",\n" +
                "  \"DRSToBI_OffloadJob_1\",\n" +
                "  \"Update_HCatalog\",\n" +
                "  \"DRSToS3\",\n" +
                "  \"S3ToBI_OffloadJob_2\",\n" +
                "  \"S3ToBI_OffloadJob_3\"\n" +
                "]")));


        request=get("/dsapi/dstage1/jobs");
        mvc.perform(request).andExpect(status().isOk()).andExpect(content().string(equalTo("[test_gcc]")));

        request=get("/dsapi/status/dstage1/jobs");
        mvc.perform(request).andExpect(status().isOk()).andExpect(content().string(equalTo("DSJS_RUNOK")));

        request=get("/dsapi/runwait/dstage1/jobs");
        mvc.perform(request).andExpect(status().isOk()).andExpect(content().string(equalTo("DSJS_RUNOK")));

        request=get("/dsapi/rundaemon/dstage1/jobs");
        mvc.perform(request).andExpect(status().isOk()).andExpect(content().string(equalTo("DSJS_RUNNING")));

    }*/
}
