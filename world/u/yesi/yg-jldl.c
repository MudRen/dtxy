inherit __DIR__"guai.c";
#include <ansi.h>

void set_skills(int max_value, int level)
{
        int guai_value;
        ::set_skills(max_value, level);
        
       	if (level==1) guai_value = max_value+max_value/8;
	else if (level==2) guai_value = max_value+max_value/6;
	else guai_value = max_value+max_value/4;
        set("title", HIG"借力打力"NOR);
        set_skill("literate", 150);
       	set_skill("stick", guai_value+random(16));
	set_skill("sword", guai_value+random(16));
	set_skill("liangyi-sword", guai_value+random(16));
	set_skill("dao", guai_value+20+random(16));
	set_skill("puti-zhi", guai_value+random(16));
	set_skill("wuxiangforce", guai_value+random(16));
	set_skill("qianjun-bang", guai_value+random(16));
	set_skill("jindouyun", guai_value+random(16));
	map_skill("spells", "dao");
	map_skill("unarmed", "puti-zhi");
	map_skill("force", "wuxiangforce");
	map_skill("stick", "qianjun-bang");
	map_skill("parry", "qianjun-bang");
	map_skill("dodge", "jindouyun");
	map_skill("sword", "liangyi-sword");
	create_family("方寸山三星洞", 3, "弟子");
	set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
        (: perform_action,"stick", "qiankun" :),
        }) );
	set("force_factor", query_skill("force")/2);
	set("mana_factor", query_skill("spells",1));
	
                
        carry_object("/d/obj/armor/jinjia.c")->wear();
        carry_object("/d/sea/obj/dragonstick.c")->wield();
}


void heart_beat() {      
   
   if (!query_temp("jldl") && is_fighting())
      command("exert jldl");
      ::heart_beat();
}

