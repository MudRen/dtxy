inherit NPC;
#include "star.h"
 
void create()
{
        set_name("ͯ��", ({"dohko", "tian chen"}));
        set("long", "��˵����®ɽ���Ϸ徲��243����й���������,��ƽ������һ����
�ƽ�ʥ��ʿ�����𿴹ܱ��ŵ��ȷ�ӡ��һ�������ڤ��ʿ��������
���ȴ��践�ϻ�ͯ���� \n");
        set("gender","����");
        set("title", "��"+HIY"�ƽ�ʥ��ʿ"+NOR"��");
        set("age",300);
        set("con",30);
        set("per",30);
        set("str",25);
        set("int",35);
        set("combat_exp",4000000);
        set("chat_chance",20);
        set("chat_msg", ({
                "ͯ��˵����ֻ�ж���������õĹ���\n",
        }));
        set_skill("dodge", 300);
        set("attitude", "friendly");
        set_skill("force", 300);
        set_skill("parry", 300);
        set_skill("unarmed", 300);
//        set_skill("staff", 300);
//        set_skill("lunhui-zhang",300);
        set_skill("dragonfight",300);
        set_skill("dragonstep",300);
        set_skill("spells",300);
        set_skill("seashentong", 300);
//        map_skill("staff","lunhui-zhnag");
        map_skill("unarmed","dragonfight");
        map_skill("spells","seashentong");
        map_skill("dodge","dragonstep");
        map_skill("parry","dragonfight");

		set("max_force", 6000);
        set("force", 13000);
        set("max_mana",7000);
        set("mana",14000);
        set("mana_factor",100);
        set("force_factor",0);
        set("max_kee", 3500);
        set("max_gin", 3500);
        set("max_sen", 3500);

        setup();
        carry_object(__DIR__"obj/tc_cloth")->wear();
   //     carry_object("/d/obj/weapon/staff/tc_staff")->wield();
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

     switch(random(5))
     {        
        case 0:
        {
        message_vision(HIC"$N��һ����®ɽ�����ԡ�һ�������Ծ������ֱ��$n��\n",ob,me);

        if(random(2)==0)
                {
              message_vision(HIC"$N�������ڿ��ж��÷��˼�ʮ����ͷ��\n"NOR,me);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        else        message_vision(HIG"$N���ͼ�ת����֪�����˶���Ȧ�Ŷ�������Ĺ�����\n"NOR,me);
        }
        break;


        case 1:
        {

        message_vision(YEL"$N�ߺ�һ������®ɽ�����ԡ���һ�������Խ��׶�����β����$nɨȥ��\n",ob,me);

        if(random(2)==0)
                {
              message_vision(GRN"$N��������β��˦�˸����ţ�$N��ʱ��ð���ǣ�\n"NOR,me);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        else
        message_vision(HIY"$N�þ�ȫ������������������������β������$N�Ľŵװ�ɨ����\n"NOR,me);
        } 
        break;

        case 2:
        {

        message_vision(HIR"$N�ߺ�һ������®ɽ�����ԡ�������ֻ������$n�������\n",ob,me);

                if(random(2)==0)

                {
              message_vision(HIR"$N��һ����һ����������ֻ�����ڿ���ϷŪ�ţ�\n"NOR,me);
              me->add("eff_kee",-3*query("max_kee")/10);
              me->add("eff_sen",-3*query("max_sen")/10);
                }
        else
        message_vision(HIR"$N��׼�˾���֮��Ŀ�϶����ת��ת������ǿ���ѣ�\n"NOR,me,ob);
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
		
        message("chat",HIY+"���ƽ�ʮ�������ŵ���(Athena):"+ob->name()+
        "�����˵��߹�����ӹ�!\n"NOR,users());
    }

 if((ob&&ob->query("12gong/shinu")=="done") && (ob&&ob->query("12gong/tiancheng")!="done"))
{
     message("say","\nͯ������˵��:���ܴ����֤���������ǿ��,�Ժ��ս������Ӽ���,�Ҵ���һ������(tianlong),
������Σ�յ�ʱ���м����ã�\n"NOR,ob);
       ob->set_temp("12gong/tianlong","done");
	   message_vision(HIY"\n\nͯ��˵�����ʧ��,�����Ͻ���������һ����������Ӱ,�ֽ�����ȥ��.\n"NOR,ob);
     ob->start_busy(3);
              ob->set("12gong/tiancheng","done");
     ob->add("12gong/number",1);
      ob->add("daoxing", 10000);
       tell_object(ob,"��Ӯ����ʮ�����");
}
        if (ob->query_temp("12gong/cike") == "done")
    {
        message("chat",HIY+"���ƽ�ʮ������ͯ��(Dohko):"+ob->name()+
        "�Ѿ���������ӹ�!\n"NOR,users());
		::die();
		}

      destruct(this_object());
}

void unconcious()
{
  die();
}
