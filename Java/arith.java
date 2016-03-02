class arith extends c2jrt
{
   private static String class_name = "arith";


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
static int strarith2= jtocstr("Enter the n-th and m-th number of arithmetical progression: ");
static int strarith3= jtocstr("\n %lf%lf");
static int strarith4= jtocstr("Enter indexes of this numbers: ");
static int strarith5= jtocstr("\n %d%d");
static int strarith6= jtocstr("\n %lf");
   
   /* file C:/GCC/C_programmes/arith.c line 4*/
   
   public static int cmain()
   {
      nextlevel();
      if(true)
      {
      int label= 0;
      int retval= 0;
      int cn_3=alloconstack(0);
      int cm_4=alloconstack(0);
      int  ci_5= 0;
      int ca_6=alloconstack(0);
      int cb_7=alloconstack(0);
      double  cd_8= 0;
      int y1= 0;
         
         {
         setMEMINT((int)(cn_3),(int)(0));
         setMEMINT((int)(cm_4),(int)(0));
         ci_5= 0;
         setMEMINT((int)(ca_6),(int)(0));
         setMEMINT((int)(cb_7),(int)(0));
         cd_8= 0;
         
         /* file C:/GCC/C_programmes/arith.c line 7*/
         cprintf(strarith2,0);
         startargs(ca_6);
         addarg(cb_7);
         
         /* file C:/GCC/C_programmes/arith.c line 8*/
         cscanf(strarith3,endargs());
         
         /* file C:/GCC/C_programmes/arith.c line 9*/
         cprintf(strarith4,0);
         startargs(cn_3);
         addarg(cm_4);
         
         /* file C:/GCC/C_programmes/arith.c line 10*/
         cscanf(strarith5,endargs());
         cd_8=((getMEMDOUBLE((int)(cb_7)) - getMEMDOUBLE((int)(ca_6)))/(double)((getMEMINT((int)(cm_4)) - getMEMINT((int)(cn_3)))));
         
         /* file C:/GCC/C_programmes/arith.c line 17*/
         ci_5=getMEMINT((int)(cn_3));
         lab_arith0 : for( ; (((ci_5)<=(getMEMINT((int)(cm_4))))?1:0)!=0 ; )
         {
            
            {
            y1= (int)(ca_6);
            setMEMDOUBLE((int)(y1),(double)((getMEMDOUBLE((int)(y1)) + cd_8)));
            startargs(getMEMDOUBLE((int)(ca_6)));
            
            /* file C:/GCC/C_programmes/arith.c line 16*/
            cprintf(strarith6,endargs());
            
            }
         ci_5++;
         
         }
         retval= 0;
         if(true)
         {
         prevlevel();
         return retval;
         };
         
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
