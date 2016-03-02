class new extends c2jrt
{
   private static String class_name = "new";


   static Class pcmain[]=null;
   public static int cmain;

   static
   {
    try
   {
      cmain=getMethod(Class.forName(class_name),"cmain",pcmain);
   }catch(Exception ex){
    ex.printStackTrace();
   }
   }
   
   /* file C:/GCC/C_programmes/new.c line 5*/
   
   public static int cmain()
   {
      nextlevel();
      if(true)
      {
      int label= 0;
      int retval= 0;
      int  cn_3= 0;
      int  cshootingX_4= 0;
      int  ci_5= 0;
         
         {
         cn_3= 10;
         cshootingX_4= (int)(
         /* file C:/GCC/C_programmes/new.c line 7*/
         cmalloc((8*cn_3)));
         ci_5= 0;
         
         /* file C:/GCC/C_programmes/new.c line 12*/
         ci_5=0;
         lab_new0 : for( ; (((ci_5)<(cn_3))?1:0)!=0 ; )
         {
            
            {
            setMEMDOUBLE((int)((cshootingX_4 + ((int)(ci_5)*8))),(double)(ci_5));
            
            }
         ci_5++;
         
         }
         
         /* file C:/GCC/C_programmes/new.c line 16*/
         ci_5=0;
         lab_new1 : for( ; (((ci_5)<((cn_3/2)))?1:0)!=0 ; )
         {
            
            {
            setMEMDOUBLE((int)((cshootingX_4 + ((int)(ci_5)*8))),(double)(getMEMDOUBLE((int)((cshootingX_4 + ((int)(((cn_3 - ci_5) - 1))*8))))));
            
            }
         ci_5++;
         
         }
         
         }
      };
      prevlevel();
      return 0;
   }

   public static void main(String[] args)
   throws Exception
   {
      int argc=args.length;
      int argv;
      
      nextlevel();
      argv = makeargv(new Object(), args, argc);
      c_c2jstartup ();
      {
      cmain();
      }
      c_c2jexit();
      prevlevel();
   
   }
}
