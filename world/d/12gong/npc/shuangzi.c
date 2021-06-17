inherit NPC;
#include "star.h"
 
void create()
{
        set_name("˫����ʥ��ʿ", ({"shuang zi"}));
        set("long", "�ػ�˫�����Ļƽ�ʥ��ʿ,��������������һ�����ˡ�\n");
        set("gender","����");
        set("title", "��"+HIY"�ƽ�ʥ��ʿ"+NOR"��");
        set("age",37);
        set("con",30);
        set("per",30);
        set("str",25);
        set("int",35);
         set("combat_exp",8000000);
          set("daoxing",8000000);
        set("chat_chance",20);
        set("chat_msg", ({
                "˫����ʥ��ʿ���������Ŀ�����,����ȫ�������\n"   
        }));
        set_skill("dodge", 250);
       set("attitude", "aggressive");

        set_skill("force", 250);
        set_skill("parry", 250);
        set_skill("unarmed", 250);
        set_skill("sword", 250);
        set_skill("westsword",250);
        set_skill("boxing",250);
        set_skill("balei",250);
        set_skill("spells",250);
        set_skill("shuangzi", 250);
        map_skill("sword","westsword");
        map_skill("unarmed","boxing");
        map_skill("spells","shuangzi");
        map_skill("dodge","balei");
        set("max_force", 4000);
        set("force", 8000);
        set("max_mana",4500);
        set("mana",9000);
        set("mana_factor",180);
        set("force_factor", 150);
        set("max_kee", 2000);
        set("max_gin", 2000);
        set("max_sen", 2000);

        setup();
        carry_object(__DIR__"obj/sz_cloth")->wear();
        carry_object("/d/obj/weapon/sword/westsword")->wield();
}
 
void init()
{
        object me=this_player();
		::init();
		if( !me || !visible(me) || environment(me) != environment() ) return;
		
		message_vision(HIY"\n��ֻ����������һ�����صĿռ�,�����ж������˹��������!\n\n"NOR,me); 
		add_action("do_none","perform");
        add_action("do_none","cast");
        add_action("do_none","ji");
}

void check()
{
        object ob=this_object();
        object me=query_temp("my_killer");
        if( ! me ) return ;

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
        message_vision(HIG"$N�ͷų�С����[�ƽ����Ԫ]��һ�����Х����\n",ob,me);

        if(random(3)==0)

                {
              message_vision(HIG"$N��������Ԫ�ռ䣬���ް��������\n"NOR,me);
              me->add("eff_kee",-query("max_kee")/10);
              me->add("eff_sen",-query("max_sen")/10);
                }
        else
        message_vision(HIG"$N�ڷ�����ת�ţ������������������ս��\n"NOR,me);
        }
        break;


        case 1:
        {

        message_vision(HIC"$N�ٴ�ʹ��[�ƽ����Ԫ]��һ����������$n��\n",ob,me);

        if(random(3)==0)

                {
              message_vision(HIC"$N���������˸����ţ�ֱ���ͷƤ���飡\n"NOR,me);
              me->add("eff_kee",-2*query("max_kee")/10);
              me->add("eff_sen",-2*query("max_sen")/10);
                }
        else
        message_vision(HIC"$N��Ϳ���������ķ�������һ�����㿪�ˡ�\n"NOR,me);
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
        
		 if((ob&&ob->query("12gong/jinniu")=="done") && (ob&&ob->query("12gong/shuangzi")!="done"))
         {
        
		ob->start_busy(3);
         
        message("chat",HIY+"���ƽ�ʮ����������(Sa ga):��Ȼ������ǿ�����ҵ�˫���Թ�������������\n"NOR,users());
        ob->set("12gong/shuangzi","done");
        ob->add("12gong/number",1);
        ob->add("combat_exp", 10000);
        tell_object(ob,"��õ���ʮ�����\n");
		
		}
        ob->move("/d/12gong/sz2jx1"); 
		ob->delete_temp("12gong/szkill");
	//    ob->set_temp("12gong/szgo");
	//	call_other("/d/12gong/szchoose","???");
    //    find_object("/d/12gong/szchoose")

		message_vision("\n\n��˫�����ƽ�ʥ��ʿ��,���ص������漴��ʧ,Ť����ʱ��Ҳ�ָ���ԭ״!\n\n"NOR,ob);
        message_vision("\n����һ������,˫�ӹ���������ȥ.\n\n"NOR,ob);
//	   ::die();
	   destruct(this_object());

}

int do_none()
{
        object me = this_object();

        message_vision("$N����һ������ë���Ȼ����Ц!\n",me);
        return 1;
}

void unconcious()
{
  die();
}
