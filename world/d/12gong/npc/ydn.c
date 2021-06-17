// by ����(take)
inherit NPC;
string ask_cloth();
#include <ansi.h>

void create()
{
   set_name("�ŵ���", ({ "athena", "na" }));
   set("long", @LONG

LONG);
   set("gender", "Ů��");
   set("age", 20);
   set("attitude", "peaceful");
   set("per",100);//means no rong-mao description.
   set("max_kee", 12000);
   set("max_gin", 14000);
   set("max_sen", 12000);
   set("force", 12000);
   set("max_force", 24000);
   set("force_factor", 500);
   set("max_mana", 14000);
   set("mana", 28000);
   set("mana_factor", 600);
   set("combat_exp", 20000000);
   set("daoxing", 20000000);
   set_skill("spells", 900);
   set_skill("buddhism", 900);
   set_skill("unarmed", 900);
   set_skill("jienan-zhi", 900);
   set_skill("dodge", 900);
   set_skill("lotusmove", 900);
   set_skill("parry", 900);
   set_skill("force", 900);
   set_skill("lotusforce", 900);
   set_skill("staff", 900);
   set_skill("lunhui-zhang", 900);
   map_skill("spells", "buddhism");
   map_skill("unarmed", "jienan-zhi");
   map_skill("dodge", "lotusmove");
   map_skill("force", "lotusforce");
   map_skill("parry", "lunhui-zhang");
   map_skill("staff", "lunhui-zhang");
   set("no_get","���ŵ��ȵ������,�����Ҷ�Ů�񲻾�?\n");
   set("chat_chance_combat", 90);
   set("inquiry",([
      "�ƽ�ʥ��": (: ask_cloth:) ]));

   setup();
  carry_object("/d/12gong/obj/armor")->wear();
   carry_object("/d/12gong/obj/cloth")->wear();
  carry_object("/d/12gong/obj/pifeng")->wear();
     carry_object("/d/12gong/obj/shield")->wear();
carry_object("/d/12gong/obj/staff")->wield();
}

string ask_cloth()
{
        object ob = this_object();
        object me = this_player();
        object cloth;
        if( me->query("12gong/number") >= 12 && !me->query("12gong/all") )
        {
        	command_function("chat "HIY+me->name()+"����ĥ�ѣ����ڵõ��˻ƽ�ʥ�£�");
        	me->set("12gong/all",1);
            	cloth=new("/d/12gong/obj/gold_cloth.c");
        	cloth->move(me);
 		me->add("daoxing",100000);
		me->add("potential",100000);
		me->add("combat_exp",100000);
		return "��õ���100����У�10���Ǳ�ܣ�10�����ѧ���ƽ�ʥ��һ����\n���Ҫע����,���������,�������Լ���ʥ�¸�(drop)��,��ֻ���ٴ��ƽ�ʮ������!";
        }
	else if (me->query("12gong/all") && me->query("12gong/number") >= 12 && !present("huangjin shengyi",me) )
	{
     		cloth=new("/d/12gong/obj/gold_cloth.c");
		cloth->move(me);
  		return "�ú����ţ�����Ū����Ŷ";
	}
	else if( present("huangjin shengyi",me) )
		return "̰�Ŀɲ��ã�";
	else
        	return "�㻹����ͨ��ʮ�����Ŀ���ɣ�";

}
