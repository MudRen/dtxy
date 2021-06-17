//created by vikee
//2000-12-9 23:35
inherit NPC;
#include <ansi.h>
void leave();
void leave2();
void create()
{
	set_name("����", ({ "jian ling", "jian" }));
	set("family/family_name","��ɽ��");
	set("age", 500+random(80));
	set("class", "yao");
	set("combat_exp", 3000);
	set("attitude", "heroism");
	set_skill("unarmed", 10);
	set_skill("jinghun-zhang", 10);
	map_skill("unarmed", "jinghun-zhang");
	set_skill("dodge", 10);
	set_skill("ghost-steps", 10);
	map_skill("dodge", "ghost-steps");
        setup();
}

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;
        me->set_skill("unarmed", j);
        me->set_skill("dodge", j);
        me->set_skill("parry", j);
        me->set_skill("force", j);
        me->set_skill("spells", j);
        me->set_skill("sword",j); 
        
        me->set_skill("yujianshu", j+random(15));
	me->set_skill("mindsword", j+random(15));        
        me->set_skill("spells",j+random(15));
        me->set_skill("sevensteps",j+random(15));
        me->set_skill("taoism", j+random(15));
        me->set_skill("unarmed", j+random(15));        
        me->set_skill("hunyuan-zhang", j+random(15));
        me->set_skill("zixia-shengong", j+random(15)); 

        me->map_skill("force", "zixia-shengong");
        me->map_skill("sword", "mindsword");        
        me->map_skill("parry", "mindsword");
        me->map_skill("spells", "taoism");
        me->map_skill("dodge", "sevensteps");
        me->map_skill("unarmed", "hunyuan-zhang");
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                (: exert_function, "zhanqi" :),
                (: exert_function, "huti" :),
                (: exert_function, "recover" :),
                (: cast_spell, "chaoyuan" :),
        }) );
	carry_object("/d/obj/weapon/sword/qingfeng")->wield();
        carry_object("/d/obj/cloth/shoupiqun")->wear();
}

void copy_status(object me,object ob, int lv)
{
        int j, lvl,k,m;
        object qm=new("/d/changan/npc/qianmian.c");
	int base=20;

	lvl=lv+base-2;

        if(qm) {
            mapping skill=ob->query_skills();
            int i=sizeof(skill);
            int *level, max_level;
	    int max_sen, max_kee;

	    if(i>0) {
		level=values(skill);
		max_level=level[0];
		while(i--) { // find out victim's maximum level
		    if(level[i]>max_level)
			max_level=level[i];
		}
	        max_level=max_level*lvl/base;

	    } else max_level=1;

	    qm->copy_status(this_object(), ob, lvl);
            destruct(qm);

	    k=(query("daoxing")+query("combat_exp"))/2;
	    for(m=1;m<300;m=m+10) {
		if(m*m*m/10>k) break;
	    }
	    m=m*lvl/base/3;
	    if(max_level<m) max_level=m;

	    // skill level will be set to the maximum level
	    // of the player.
	    set_skills(max_level, lv);
	    set("owner",ob);
	    max_sen=query("max_sen")/4;
	    max_kee=query("max_kee")/4;
	    add("eff_sen",max_sen);
	    add("eff_kee",max_kee);
	    add("sen",max_sen);
	    add("kee",max_kee);
	    add("max_sen",max_sen);
	    add("max_kee",max_kee);

	} else { // sth goes wrong.
	    leave();
	    return;
	}

	  add("force",query("force")); // double force.
	                               // because players have fabao.
	                             // mana is doubled when copying.
        set("force_factor", query_skill("force")/2);
        set("mana_factor", query("max_mana")/30+1);
	
	set("daoxing",(query("daoxing")*2+query("combat_exp"))/3);
}

void unconcious()
{
 	die();
}
void die()
{
	object who = this_object()->query_temp("last_damage_from");
	if( !objectp(who) )
		return;
	if( who->query("betray/count") )
		return;
	if( who->query("family/family_name") != "��ɽ��" )
                return;
	if( query("kee") > 1 && query("sen") > 1 )
		return ;
	if( who == query("owner") && !who->query("sword_cant") )
	{
		message_vision(HIY"$N���ػ���һ����������$n����Χס����Ҫ����$n���ڡ�\n"NOR,this_object(),who);
		if( !who->query("sword_known") && random(who->query("int")) > 16 - random( who->query("lunhui_zhuanshi") ) )
		{
			who->add("sword_known",1);
			message_vision(HIY"$n���ܵ�$N�ڰ����Ľ��⣬�ſ�������������������ڡ�\n"NOR,this_object(),who);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(jian ling)��" + who->name() + "���Թ��ˣ�ͨ��ս����ᵽ��"+HIY"[����]"+HIC"�Ĵ��ڣ�\n\n\n"NOR,users());
		}
		else if( who->query("sword_known") == 1 && random(who->query("int")) > 18 - random( who->query("lunhui_zhuanshi") ) )
		{
			who->add("sword_known",1);
			message_vision(HIY"$n���ܵ�$N�ڰ����Ľ��⣬�ſ�������������������ڡ�\n"NOR,this_object(),who);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(jian ling)��" + who->name() + "���Թ��ˣ�ͨ�����ϵ�ս������"+HIY"[����]"+HIC"�������һ����\n\n\n"NOR,users());
		}
		else if( who->query("sword_known") == 2 && random(who->query("int")) > 20 - random( who->query("lunhui_zhuanshi") ) )
		{
			who->add("sword_known",1);
			message_vision(HIY"$n���ܵ�$N�ڰ����Ľ��⣬�ſ�������������������ڡ�\n"NOR,this_object(),who);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(jian ling)��" + who->name() + "���Թ��ˣ�ͨ�����ϵ�ս������"+HIY"[����]"+HIC"�������һ����\n\n\n"NOR,users());
		}
		else if( who->query("sword_known") == 3 && random(who->query("int")) > 22 - random( who->query("lunhui_zhuanshi") ) )
		{
			who->add("sword_known",1);
			message_vision(HIY"$n���ܵ�$N�ڰ����Ľ��⣬�ſ�������������������ڡ�\n"NOR,this_object(),who);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(jian ling)��" + who->name() + "���Թ��ˣ�ͨ�����ϵ�ս������"+HIY"[����]"+HIC"�������һ����\n\n\n"NOR,users());
		}
		else if( who->query("sword_known") == 4 && random(who->query("int")) > 24 - random( who->query("lunhui_zhuanshi") ) )
		{
			who->add("sword_known",1);
			message_vision(HIY"$n���ܵ�$N�ڰ����Ľ��⣬�ſ�������������������ڡ�\n"NOR,this_object(),who);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(jian ling)��" + who->name() + "���Թ��ˣ�ͨ�����ϵ�ս������"+HIY"[����]"+HIC"�������һ����\n\n\n"NOR,users());
		}
		else if( who->query("sword_known") == 5 && random(who->query("int")) > 26 - random( who->query("lunhui_zhuanshi") ) )
		{
			who->add("sword_known",1);
			message_vision(HIY"$n���ܵ�$N�ڰ����Ľ��⣬�ſ�������������������ڡ�\n"NOR,this_object(),who);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(jian ling)��" + who->name() + "���Թ��ˣ�ͨ�����ϵ�ս������"+HIY"[����]"+HIC"�������һ����\n\n\n"NOR,users());
		}
		else if( who->query("sword_known") == 6 && random(who->query("int")) > 28 - random( who->query("lunhui_zhuanshi") ) )
		{
			who->add("sword_known",1);
			message_vision(HIY"$n���ܵ�$N�ڰ����Ľ��⣬�ſ�������������������ڡ�\n"NOR,this_object(),who);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(jian ling)��" + who->name() + "���Թ��ˣ�ͨ�����ϵ�ս������"+HIY"[����]"+HIC"�������һ����\n\n\n"NOR,users());
		}
		else if( who->query("sword_known") == 7 && random(who->query("int")) > 30 - random( who->query("lunhui_zhuanshi") ) )
		{
			who->add("sword_known",1);
			message_vision(HIY"$n���ܵ�$N�ڰ����Ľ��⣬�ſ�������������������ڡ�\n"NOR,this_object(),who);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(jian ling)��" + who->name() + "����������������Ϊһ�壬��ȫ������"+HIY"[����]"+HIC"��������\n\n\n"NOR,users());
		}
		else
		{
			who->set("sword_cant",1);
			message_vision(HIY"$n�޷����$N�Ķ��������к��£��Ͻ��˹��ر��������$N�������⡣\n"NOR,this_object(),who);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(jian ling)��" + who->name() + "��Ե�������ղ�����ȫ����"+HIY"[����]"+HIC"�����������ǿ�ϧ��\n\n\n"NOR,users());
		}
	}
	else
		message_vision("$N���ˡ�\n",this_object());
	who->move("/d/shushan/shengdi/kongdi");
	destruct(this_object());
}

varargs int receive_damage(string type, int damage, object who)
{
	if( !objectp(who) )
		 return damage;
  	if( who->query_temp("sword_type") > who->query("sword_known")-1 ) 
  		return ::receive_damage(type,damage,who);
  	return damage;
}
varargs int receive_wound(string type, int damage, object who)
{
	if( !objectp(who) )
		 return damage;
  	if( who->query_temp("sword_type") > who->query("sword_known")-1 ) 
  		return ::receive_wound(type,damage,who);
  	return damage;
}
void leave()
{
      if(this_object()) { 
        if(environment())
          message("vision",HIB + name() + 
		  "����һ�Σ����һ������ɢȥ�ˡ�\n" NOR,environment());
	this_object()->move("/obj/empty");
	call_out("leave2",5);
      }
      return;
}

void leave2()
{
    if(this_object()) {
	destruct(this_object());
    }
}