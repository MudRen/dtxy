// by happ@YSZZ
 
inherit NPC;
#include "star.h"

 
void create()
{
        set_name("��ŷ����", ({"aiolia", "shi zi"}));
        set("long", "ʨ��������һͷ�ƽ�ʨ�Ӱ㣬������������������ڤ��֮ս�У�
��һȭɱ������ڤ��ʿ������ط������׵ļ�ս�У�����ȡ��ʤ���������ػ���ʨ������\n");
        set("gender","����");
        set("title", "��"+HIY"�ƽ�ʥ��ʿ"+NOR"��");
        set("age",37);
        set("con",40);
        set("spi",50);
        set("per",30);
        set("str",35);
        set("int",45);
          set("combat_exp",10000000);
        set("daoxing",10000000);
        set("chat_chance",20);
        set("chat_msg", ({
                "��ŷ����˵������֪��ʱ���ټ����ŵ��ȣ�\n"   
        }));
        set("attitude", "friendly");
        set_skill("dodge", 280);
        set_skill("force", 280);
        set_skill("parry", 280);
        set_skill("unarmed", 280);
        set_skill("sword", 280);
        set_skill("westsword",280);
        set_skill("boxing",280);
        set_skill("balei",280);
        set_skill("spells",280);
        set_skill("jinniu", 280);
        map_skill("sword","westsword");
        map_skill("unarmed","boxing");
        map_skill("spells","jinniu");
        map_skill("dodge","balei");
        set("max_force", 5000);
        set("force", 9000);
        set("max_mana",5000);
        set("mana",9000);
        set("mana_factor",50);
        set("force_factor", 150);
        set("max_kee", 2500);
        set("max_gin", 2500);
        set("max_sen", 2500);

        setup();
        carry_object(__DIR__"obj/shz_cloth")->wear();
        carry_object("/d/obj/weapon/sword/westsword")->wield();
}
 
void init()
{
        
        object me=this_player();
		::init();
        add_action("do_nod", "nod");
		if (me->query_temp("12gong/cike") != "done")
			{
           	command("say ���ú�,�ҵ���ܾ���,�ܹ�����ʨ�ӹ�����һ����Ů����ѡ��
������ʿ,սʤ�Ҳ���֤���������������!��׼��������?(nod)\n\n\n");
        	}
if (me->query_temp("12gong/cike") == "done")
	{
	command("say �ô�ĵ���,��������ɱ[Ů��] �ŵ���,�ȹ�����һ�أ�\n");
    message_vision(HIY"\nŭ������İ�ŷ����ȫ��ƽ�����ʢ,һͷ���͵Ļƽ�ʨ���Ѿ�������˹���!!!\n"NOR,me);	
	kill_ob(me);
    set_skill("dodge", 300);
        set_skill("force", 300);
        set_skill("parry", 300);
        set_skill("unarmed", 300);
        set_skill("sword", 300);
        set_skill("westsword",300);
        set_skill("boxing",300);
        set_skill("balei",300);
	}
}


void check()
{
        object ob=this_object();
        object me=query_temp("my_killer");
        if( ! me ) return ;

 if( me->is_ghost() )
     {
     remove_call_out("check");
     return;
     }
if(!present(me,environment()) )
     {
     remove_call_out("check");
     return;
     }
     switch(random(6))
     {        
        case 0:
        {
        message_vision(HIC"$N�ſ����죬��Ȼ�ó�һͷ�ƽ�ʨ�ӣ�����$n��\n",ob,me);

        if(random(2)==0)
                {
              message_vision(HIC"�ƽ�ȭͷ����������$N�����ϣ�\n"NOR,me);
              me->add("eff_kee",-query("max_kee")/10);
              me->add("eff_sen",-query("max_sen")/10);
                }
        else
        message_vision(HIC"$N���һ������Ȼ�ѻƽ��������˻�ȥ��\n"NOR,me);
        }
        break;


        case 1:
        {

        message_vision(HIC"$N��ָ̫����ֻ������ͻȻ��ǿ���յ����������ۣ�\n",ob,me);

                if(random(2)==0)

                {
              message_vision(HIC"$N�о����������������ʹ��\n"NOR,me);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        else
        message_vision(HIC"��������$N�����ϣ�$N�е����޵�Ͼ�⡣\n"NOR,me);
        }
        break;

        case 2:
        {

        message_vision(HIC"$Nʹ��[�������ȭ]������һͷ�ƽ�ʨ����$n��ȥ��\n",ob,me);
                              
                if(random(2)==0)

                {
              message_vision(HIY"$N��֪����Ǻã���Ȼ����������ȭ��\n"NOR,me);
              me->start_busy(1);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        else
        message_vision(HIC"$N�����۾���ƾ�Է������Ķ����жϹ�������,�������������һ����\n"NOR,me,ob);
        }
        break;

  }
        if( random(8) == 5 )
        powerup();

        remove_call_out("check");
        call_out("check",2+random(3));
}
void die()
{

        object ob = query_temp("my_killer");

        if((ob&&ob->query("12gong/juxie")=="done") && (ob&&ob->query("12gong/shizi")!="done"))
        {
        if (ob->query_temp("12gong/cike") == "done")
			
			 message("chat",HIY+"���ƽ�ʮ��������ŷ����(Aiolia):"+ob->name()+
             "ǿ�������幬ʨ�������ƽ�ʥ��ʿ��������Ů��-�ŵ��ȡ�\n"NOR,users());
             else
         message("chat",HIY+"���ƽ�ʮ�������ŵ���(Athena):"+ob->name()+
             "�����˵��幬ʨ������������Ů��ǰ����\n"NOR,users());
			 ob->start_busy(3);
			 ob->set("12gong/shizi","done");
             ob->add("12gong/number",1);
             ob->add("combat_exp", 10000);
             tell_object(ob,"��Ӯ����ʮ�����");

        }
       ::die();
       return 0;
}


int do_nod(string arg)
{
	
	object me=this_player(), npc=this_object(), ob;
	if (me->query_temp("12gong/cike") != "done")
	//string myname=me->query("id");
    {
		command("say С����!!!\n");
        kill_ob(me);
        message_vision(HIY"\n��ŷ����ȫ��ƽ�����ʢ,����һͷ���͵Ļƽ�ʨ��!\n"NOR,me);	
 	}
return 0;

}

void unconcious()
{
  die();
}
