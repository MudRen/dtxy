// by happ@YSZZ
 
inherit NPC;
#include "star.h"
 
void create()
{
        set_name("ɳ��", ({"sa ga", "shi nu"}));
        set("long", "��ӽ�������ˣ��ƽ�ʥ��ʿ����ǿ�ߡ�����ڤ��֮ս��ɱ������
ڤ��ʿ����󣬺������ƽ�ʥ��ʿͬ���ھ�����ʵ��δ����������
���˰˸У�����ڤ�硣�ػ���Ů����\n");
        set("gender","����");
        set("title", "��"+HIY"�ƽ�ʥ��ʿ"+NOR"��");
        set("age",37);
        set("con",30);
        set("per",30);
        set("str",25);
        set("int",35);
        set("combat_exp",15000000);
        set("daoxing",15000000);
        set("chat_chance",20);
        set("chat_msg", ({
                "ɳ�ӱ���˫��,��������������ɯ��˫����,ĬĬ�Ķ�����.\n"   
        }));
        set_skill("dodge", 280);
        set("attitude", "friendly");
        set_skill("force", 280);
        set_skill("parry", 280);
        set_skill("unarmed", 280);
        set_skill("sword", 280);
        set_skill("westsword",280);
        set_skill("boxing",280);
        set_skill("balei",280);
        set_skill("spells",280);
        set_skill("shinu", 280);
        map_skill("sword","westsword");
        map_skill("unarmed","boxing");
        map_skill("spells","shinu");
        map_skill("dodge","balei");
        set("max_force", 3000);
        set("force", 6000);
        set("max_mana",3000);
        set("mana",6000);
        set("mana_factor",50);
        set("force_factor", 50);
        set("max_kee", 2200);
        set("max_gin", 2200);
        set("max_sen", 2200);

        setup();
        carry_object(__DIR__"obj/su_cloth")->wear();
        carry_object("/d/obj/weapon/sword/westsword")->wield();
}
 
void init()
{
        object me=this_player();
		::init();
		if (me->query_temp("12gong/cike") == "done")
		{
	message("chat",HIC+"���ƽ�ʮ������ɳ��(Sa ga):"+me->name()+"���Ҵ��Ҵ�Ů��,�������ʶһ���������!\n"NOR,users());
   
	message_vision(HIY"\nɳ�������˷�ŭ��˫��,�ƽ�С���汬������.\n\n"NOR,me); 
	message("chat",HIC+"���ƽ�ʮ������ɳ��(Sa ga):��Ů��������["+HIY+"���豦��"+NOR""+HIC+"]\n"NOR,users());	
		add_action("do_none","perform");
        add_action("do_none","cast");
        add_action("do_none","ji");
        set_skill("dodge", 380);
//        set("attitude", "friendly");
        set_skill("force", 380);
        set_skill("parry", 380);
        set_skill("unarmed", 380);
        set_skill("sword", 380);
        set_skill("westsword",380);
        set_skill("boxing",380);
        set_skill("balei",380);
        set_skill("spells",380);
        set_skill("shinu", 380);
       set("max_force", 5000);
        set("force", 10000);
        set("max_mana",8000);
        set("mana",16000);
        set("mana_factor",100);
        set("force_factor", 200);
        set("max_kee", 2200);
        set("max_gin", 2200);
        set("max_sen", 2200);
        kill_ob(me);
		}
}

void check()
{
        object ob=this_object();
        object me=query_temp("my_killer");
        if( ! me ) return ;
   if(! present(me,environment()) )
     {
     remove_call_out("check");
     return;
     }                               


     switch(random(6))
     {        
        case 0:
        {
        message_vision(HIG"$N��������һ�ӣ�һ�����Х���𣡻ó��������˷�ӵ����$n\n",ob,me);

                if(random(3)==0)

                {
              message_vision(HIG"$N������˵��ڵ��ϣ����ް��������\n"NOR,me);
              me->add("eff_kee",-query("max_kee")/10);
              me->add("eff_sen",-query("max_sen")/10);
                }
        else
        message_vision(HIG"$N�ڷ�����ת�ţ�������������ÿ��˹�ֵĽ�����\n"NOR,me);
        }
        break;


        case 1:
        {

        message_vision(HIC"$Nһ���������飬һ�����ӿ������������㣡\n",ob,me);

                if(random(3)==0)

                {
              message_vision(HIC"$N������˸����ţ���ʱ������[�����ֻ�]�У�\n"NOR,me);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        else
        message_vision(HIC"$N��Ϳ����˽��ķ�������һ�����㿪�ˡ�\n"NOR,me);
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

        if (ob->query_temp("12gong/cike") != "done")
	{
		if((ob&&ob->query("12gong/shizi")=="done") && (ob&&ob->query("12gong/shinu")!="done"))
        {
        ob->start_busy(3);
        message("chat",HIY+"���ƽ�ʮ�������ŵ���(Athena):"+ob->name()+
        "�����˵���������Ů������ƽ�սʿ������\n"NOR,users());
        ob->set("12gong/shinu","done");
        ob->add("12gong/number",1);
        ob->add("daoxing", 10000);
        tell_object(ob,"��Ӯ����ʮ�����");

        }
	}
	   if (ob->query_temp("12gong/cike") == "done")
	{
       if((ob&&ob->query("12gong/shizi")=="done") && (ob&&ob->query("12gong/shinu")!="done"))
        {
        ob->start_busy(3);
        message("chat",HIY+"���ƽ�ʮ������ɳ��(Sa ga):"+ob->name()+
        "����ɯ��˫��,ǿ�����˴�Ů����\n"NOR,users());
        ob->set("12gong/shinu","done");
        ob->add("12gong/number",1);
        ob->add("daoxing", 10000);
        tell_object(ob,"��Ӯ����ʮ�����");

        
		}
	}
	   message_vision(HIY"\n\nɳ�ӳ�̾һ��,������������,Զ��ɯ����Ҳ����������ȥ.....\n"NOR,ob);
	   call_out("wait_time",20);
	   message_vision(HIY"\n\n����ɯ����������,ɳ�ӵ�Ҳ��ʧ��!\n"NOR,ob);     
	   destruct(this_object());
	   
}

void unconcious()
{
  die();
}

int do_none()
{
        object me = this_object();

        message_vision("$N��Цһ������[���豦��]���������ʲô������\n",me);
        return 1;
}


void wait_time() 
{
	
     
	//  return 1;     
}