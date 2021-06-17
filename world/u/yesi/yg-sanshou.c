inherit __DIR__"guai.c";
#include <ansi.h>

void set_skills(int max_value, int level)
{
        int guai_value;
        ::set_skills(max_value, level);
        
       	if (level==1) guai_value = max_value+max_value/8;
	else if (level==2) guai_value = max_value+max_value/6;
	else guai_value = max_value+max_value/4;
        set("JQB_known",1);
        set_skill("wuxing-quan", guai_value+random(16));
	set_skill("moondance", guai_value+random(16));
	set_skill("sword", guai_value+random(16));
	set_skill("snowsword", guai_value+random(16));
	//set_skill("whip", guai_value+random(16));
	//set_skill("jueqingbian", guai_value+random(16));
        set("title", HIW"漫天飞雪"NOR);
        set("gender", "女性");
	set_skill("moonforce", guai_value+random(16));
	set_skill("literate", 180);
	set_skill("moonshentong", guai_value+20+random(16));
	map_skill("spells", "moonshentong");
	map_skill("force", "moonforce");
	map_skill("unarmed", "wuxing-quan");
	//map_skill("whip", "jueqingbian");
	map_skill("sword", "snowsword");
	map_skill("parry", "snowsword");
	map_skill("dodge", "moondance");
	create_family("月宫",3 , "弟子");
	set("force_factor", query_skill("force")/2);
	set("mana_factor", query_skill("spells",1));
	                
        carry_object("/d/obj/armor/jinjia.c")->wear();
        //carry_object("/d/obj/weapon/whip/longsuo")->wield();
        carry_object("/d/obj/weapon/sword/qinghong.c")->wield();
}


void heart_beat() {      
   if (!query_temp("JQB_perform") && is_fighting())
      command("perform tian");
       ::heart_beat();
}


