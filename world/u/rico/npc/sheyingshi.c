inherit NPC;

inherit F_VENDOR;

void create()
{
     set_name("������",({"sheying shi","sheyingshi","shi","������"}));
     set("title","��Ӱʦ");
     set("gender","����");
     set("age",22);
     set("per",30);
     set("long","��λ��Ӱʦ�������ǳ�����,���ǿ����������������ҵ����ʡ�\n");
     set("combat",10000);
     set_skill("unarmed",50);
   set("no_accept",0);
     set("attitude","friendly");
     setup();


     carry_object("/d/obj/cloth/choupao")->wear();
     carry_object("/obj/toy/camera");
     add_money("gold",10);
}

void init()
{
     object ob,me;
     me=this_object();
     ::init();
     if( interactive(ob = this_player()) && !is_fighting() ) {
            remove_call_out("greeting");
            call_out("greeting", 1, ob);
     }
}

void greeting(object ob)
{

     switch( random(3) ) {
     case 0:
            say("�������߹�����΢Ц��˵������λ" +
RANK_D->query_respect(ob)
             + "����������,��������ɡ�\n",this_object());
            break;
     case 1:
            say("�����벻֪���ڿ�ʲô,���˽�����Ҳû�з�Ӧ��\n",this_object());
            break;
     case 2:
            say("������������˽��������̷������е����������ش��к���\n",this_object());
            break;
     }
}

int accept_object(object me,object ob)
{
   me=this_player();
   ob=this_object();


   if ((string)ob->query("name")=="���ϻ"
       && (string)ob->query("id")=="camera")
   {
     command("thank" + me->query("id"));
     command("bow");
     return 1;
   }
   return 0;
}

