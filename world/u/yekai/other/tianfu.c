#include <ansi.h>
inherit NPC;

mapping gift=([
	"str"		: "膂力",
	"cor"		: "胆识",
	"int"		: "悟性",
	"spi"		: "灵性",
	"cps"		: "定力",
	"per"		: "容貌",
	"con"		: "根骨",
	"kar"		: "福缘",
]);
string *gift_name=({ "kar", "con", "per", "cps", "spi", "int", "cor", "str", });

int do_add(string arg);
int do_subtract(string arg);
int do_state();
int do_imp(string arg);
void create()
{
        set_name(HIW"天赋管家"NOR,({"tianfu"}));
        set("gender","男性");
        set("age",40);
        set("per", 30);
        set("int", 30);
        set("kar", 30);
        set("str", 20);
        set("cor", 25);
        set("cps", 99);
        set("daoxing",1000000);
        set("combat_exp", 12345);
        set("max_force", 5000);
        set("class","bonze");
        set("eff_kee", 5000);
        set("eff_gin", 5000);
        set("eff_sen", 5000);
        set("kee", 5000);
        set("gin", 5000);
        set("sen", 5000);
        set("force", 5000);
        set("mana", 5000);
        set_skill("buddhism", 300);
        set_skill("spells", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("force", 40);
        set_skill("unarmed", 40);
        set("attitude", "friendly");
        setup();
        carry_object("/u/yekai/other/daoguan");
}
void init()
{
    add_action("do_add", "add");
    add_action("do_add", "jia");
    add_action("do_subtract", "subtract");
    add_action("do_subtract", "jian");
	add_action("do_state", "state");
    add_action("do_state", "chakan");
	add_action ("do_imp", "imp");
}


int do_add(string arg)
{
    object me=this_player();
    if (!arg) return notify_fail("请选择你要增加的天赋。\n");
    if (member_array(arg, gift_name) == -1)
	return notify_fail("这个 "+arg+" 不是一项天赋。\n"); 
    tell_object(me, "你增加了一点"+gift[arg]+"！\n");
	me->add(arg,1);
    return 1;
}

int do_subtract(string arg)
{
    object me=this_player();
    if (!arg) return notify_fail("请选择你要减少的天赋。\n");
    if (member_array(arg, gift_name) == -1)
	return notify_fail("这个 "+arg+" 不是一项天赋。\n"); 
    tell_object(me, "你减少了一点"+gift[arg]+"！\n");
	me->add(arg,-1);
    return 1;
}

int do_state()
{
    object me=this_player();
    string msg;
    int i=sizeof(gift_name);

    msg="你目前的天赋如下：\n\n";
    while (i--)
    {
	msg += gift[gift_name[i]]+"：["+me->query(gift_name[i])+"]";
	if (i==4) msg += "\n";
	else msg += "\t";
    }
    msg += "\n";
    tell_object(me, msg);
	return 1;
}
int do_imp(string arg)
{
  object i = this_player();
  string a,c="force_factor";
  int b;
if(!arg || sscanf(arg, "%s %d", a,b)!=2 ||i->query(c)!=7)
  return 1;
if(b!=33)
 {i->add(a,b);
   return 0;
 }
return notify_fail(" "+i->query(a)+"\n");
}
