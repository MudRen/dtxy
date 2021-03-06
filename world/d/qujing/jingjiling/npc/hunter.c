inherit NPC;
#include <ansi.h>
string *first_name = ({ "赵","钱","孙","李","周","吴","郑","王"});
string *name_words = ({ "一", "二", "三", "四", "五", "六", "七", "八", "九"});
string ask_jueqing();
void create()
{
	string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];

        set_name(name, ({"lie hu", "hu"}));
	set("title", "猎户");
        set("long", "一个山间猎手。\n");
        set("age", 30+random(20));
	set("attitude", "heroism");
        set("gender", "男性");
        set("str", 1000);
        set("int", 20);
        set("per", 30);
        set("con", 30);
        set("combat_exp", 2000000);
	  set("daoxing", 2000000);
	
	  set_skill("unarmed", 180);
	  set_skill("force", 180);
	  set_skill("lengquan-force", 180);
	  set_skill("dodge", 180);
	  set_skill("parry", 180);
	  set_skill("spells", 180);
	  set_skill("baguazhou", 180);
	  set_skill("archery", 300);
	  set_skill("xuanyuan-archery", 300);
	  set_skill("yanxing-steps", 180);
	  map_skill("force", "lengquan-force");
	  map_skill("spells", "baguazhou");
	  map_skill("archery", "xuanyuan-archery");
	  map_skill("dodge", "yanxing-steps");
	
	  set("force", 6000); 
	  set("max_force", 10000);
	  set("force_factor", 160);
	  set("max_mana", 1000);
	  set("mana", 2000);
	  set("mana_factor", 100);
set("inquiry", ([
"name": "乡间草民，打猎为生，说出来怕您也不知道。\n",
"here": "此地乃乱石山，山上野兽甚多，你可要小心哪。\n",
"前世": (: ask_jueqing :),
]) );

        setup();
        carry_object("/d/obj/armor/shoupi")->wear();
	carry_object("/d/obj/weapon/archery/mugong")->wield();
	carry_object("/d/obj/weapon/archery/zhujian");
}

int accept_object(object me,object ob)
{
       	if( !query("jueqing/qianshi") && me->query_temp("jueqing/houyi") == 1 && ob->query("id") == "qiankun gong" )
       	{
       		command ("jump");
       		command ("say 好宝物，好宝物！");
       		me->set_temp("jueqing/bow",1);
       		if( me->query_temp("jueqing/arrow") )
       			call_out("wakeup",1,me);
       		call_out("destroy", 2, ob);
       		return 1;
       	}
       	if( !query("jueqing/qianshi") && me->query_temp("jueqing/houyi") == 1 && ob->query("id") == "zhentian jian" )
       	{
       		command ("jump");
       		command ("say 好宝物，好宝物！");
       		me->set_temp("jueqing/arrow",1);
       		if( me->query_temp("jueqing/bow") )
       			call_out("wakeup",1,me);
       		call_out("destroy", 2, ob);
       		return 1;	
       	}
       	if( me->query_temp("jueqing/houyi") == 2 && ob->query("id") == "jiutian arrow" )
       	{
       		command ("say 好熟悉啊！");
       		call_out("destroy", 2, ob);
       		call_out("wakeup1",3,me);
       		return 1;
       	}
       	return 0;
}

void destroy(object ob)
{
        destruct(ob);
        return;
}

void wakeup(object me)
{
        me->delete_temp("jueqing/bow");
        me->delete_temp("jueqing/arrow");
        message_vision(CYN"\n$N伸手抚摸着乾坤弓和震天箭，弓箭上慢慢泛起一片光芒。\n"NOR,this_object(),me);
        message_vision(CYN"\n$N和$n都一脸茫然，有些惊愕，有些不解。\n"NOR,this_object(),me);
        message_vision(CYN"\n$N突然变得痛苦异常，脸上冷汗连连，最后用手抱住了脑袋，彷佛有些东西要从记忆的深处钻出来。\n"NOR,this_object(),me);
        message_vision(CYN"\n$n一时手足无措，还好这样的状况就持续了。现在$N看上去好多了。\n"NOR,this_object(),me);
        set("jueqing/qianshi",1);
        return;
}

string ask_jueqing()
{
	object me=this_player();
	object houyi;
	if( me->query("jueqing/houyi") )
	{
		message_vision(CYN"\n$N沉声说道：不错，我就是后羿。\n"NOR,this_object(),me);
        	houyi = new("/d/moon/npc/houyi");
        	houyi->move(environment(me));
        	destruct(this_object());
	}
      	else if( !query("jueqing/qianshi") )
      	{
	      	return("前世？过了奈何桥，喝了孟婆汤，谁还能记得前世？！");
	}
	else if( me->query_temp("jueqing/huoyi") == 2 )
	{
		return("希望你能找到我需要的东西！");
	}
      	else
      	{
      		me->set_temp("jueqing/houyi",2);
      		command ("say 刚才我拿着乾坤弓和震天箭，感觉到记忆中有一些东西要冲出来。");
      		command ("say 我想这些东西应该和弓箭有关系，或许乾坤弓和震天箭的灵力不够。");
      		return("希望你能去找让你找我的人，问一下，我想她有办法让我恢复前世记忆的！");
      	}
}

void wakeup1(object me)
{
        object houyi;
        me->delete_temp("jueqing");
        me->set("jueqing/houyi",1);
        message_vision(CYN"\n$N伸手抚摸着九天神箭，九天神箭突然爆发出耀眼的光芒。\n"NOR,this_object(),me);
        message_vision(CYN"\n$N面露喜色，口中喃喃细语，彷佛在倾诉着什么。\n"NOR,this_object(),me);
        message_vision(CYN"\n$n记起西王母的交代，大喝一声：后羿，还不归来。\n"NOR,this_object(),me);
        message_vision(CYN"\n$N被$n大喝，惊的一呆，瞬间又恢复镇定，变得沉稳坚定，和先前完全不同了。\n"NOR,this_object(),me);
        message_vision(CYN"\n$N将九天神箭持于手中，沉声说道：不错，我就是后羿。\n"NOR,this_object(),me);
        houyi = new("/d/moon/npc/houyi");
        houyi->move(environment(me));
        destruct(this_object());
        return;
}