inherit NPC;
#include "star.h"
int greeting(object me);


void create()
{
        set_name("�޵�ʿ", ({"xiu daoshi", "daoshi"}));
        set("long", "����һ����ɫ�޵�ʿ�ĳ���,������ס������ȫ��,������������,��֪����������,���Ա�
˫��Ҳͱ��������,Ь�ӱ���ɫ����һ�ڵ���,ֻ���ؿڵĻ�ɫʮ�ּܱ��紵����Ʈ��һ��
������ص������˿�����û��һ����ŵ���Ϣ,����ë���Ȼ��Σ�ոС� \n");
        set("gender","����");
        set("title", "���ص�");
        set("age",41);
        set("attitude", "friendly");
        set("con",30);
        set("per",30);
        set("str",25);
        set("int",35);
          set("combat_exp",100000);
          set("daoxing",2600000);
        set("chat_chance",20);
        set("chat_msg", ({
                "���ص��޵�ʿһ�������ֹ����Ĳ�֪��˵Щʲô\n"   
        }));
          set_skill("dodge", 100);
          set_skill("force", 100);
          set_skill("parry", 100);
          set_skill("unarmed", 100);
          set_skill("sword", 100);
         set_skill("westsword",100);
          set_skill("boxing",100);
         set_skill("baiyang", 100);
        set_skill("yaofa", 100);
        map_skill("sword","westsword");
        map_skill("unarmed","boxing");
        map_skill("spells","yaofa");
         set("max_force", 1000);
         set("force", 2000);
         set("max_mana",1000);
         set("mana",2000);
         set("mana_factor",50);
         set("force_factor", 50);
       set("max_kee", 1000);
       set("max_gin", 1000);
        set("max_sen", 1000);

        setup();
        carry_object(__DIR__"obj/by_cloth")->wear();
//        carry_object(__DIR__"obj/westsword")->wield();
}
 

void init()
{
        object me = this_player();
        ::init();
        add_action("do_agree", "agree");
          if(living(me))
       
//				remove_call_out("greeting");
                call_out("greeting", 1, me);
}



int greeting(object me)
{
     if( !me || !visible(me) || environment(me) != environment() ) return 0;
     
	if (me->query_temp("12gong/cike")=="done")
    	{
		command("say ��ô������������");
	    	return 0;
	}
	command("say " + "�ٺ٣���������Ҳ����ɱ�ŵ��ȵİɣ������ƽ�ʮ�����Ѿ���
���������˱�˵ɱŮ���ŵ����ˣ������ҽ���һ���취��һ����ɱ�ŵ��ȣ����Ը��
����˵��ȥ������agree��\n");
	 
}

int do_agree(string arg)
{
	 object bishou;
    object me=this_player(), npc=this_object(), ob;
	string myname=me->query("id");
	if (me->query_temp("12gong/cike")!="done")
	{
    
	command("say �������ŵ��Ⱦ������ذ�״���(stab)����û�з���һ���ᱻ����
�ģ������Ͽ��ж�������Ŷ��\n\n");
	me->set_temp("12gong/cike","done");
    bishou = new("/d/12gong/npc/obj/bishou");
bishou->move(me);
command("grin");

	return 1;
	}
return 0;
}
