package com.onlineshop.configuration;

import org.springframework.web.servlet.support.AbstractAnnotationConfigDispatcherServletInitializer;
  
public class WebAppInitializer extends AbstractAnnotationConfigDispatcherServletInitializer  {
	@Override
	protected Class<?>[] getRootConfigClasses() {
		 return new Class[] { AppConfig.class/*, SecurityConfig.class, DBConfig.class*/ };
	}
	@Override
    protected Class<?>[] getServletConfigClasses() {
        return new Class[]{AppConfig.class};
    }
    @Override
    protected String[] getServletMappings() {
        return new String[]{ "/" };
    }

}
      