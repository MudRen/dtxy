// created 4/5/1997 by snowcat
#include <ansi.h>
#include <dbase.h>

inherit ITEM;

void create()
{
  set_name(HIB "断肠集" NOR, ({ "duanchang book"})); 
  set_weight(1000);
  set("long","一本薄薄的绢书，嫦娥百般无赖之中所涂。\n");
  set("unit", "本");
  set("no_give",1);
  set("no_get",1);
  setup();
}

init ()
{
  add_action ("do_read", "read");
}

int do_read (string arg)
{
  object me = this_player();
  string *msgs = ({
    "$N轻叹：问世间情为何物？\n",
    "$N掩卷而思，似有所悟。\n",
    "$N若有所思，沉默几许……\n",
    "$N读到伤心处，禁不住泪如雨下。\n",
    "$N轻轻地摸着书，面色婉尔。\n",
    "$N小心地翻过一页，低低地叹口气。\n",
    "$N试着把书上的词句自编自唱，却是一曲凄歌断人心肠。\n",
  });
  	if(me->query("family/family_name") != "月宫" )
  	{
                tell_object (me,"你不是月宫弟子，读不懂这本书！\n");
                return 1;
        }
        if( me->query("betray/count") )
        {
		tell_object (me,"你三心二意，读不懂这本书！\n");
		return 1;
	}
        if( (string)me->query("gender") !="女性")
        {
                tell_object (me,"你非为纯阴之身,怎能知哓女儿家的心思？！\n");
                return 1;
         }
        if(me->query("jueqing_cant"))
        {
      		tell_object(me,"你与绝情无缘！\n");
      		return 1;
      	}
        if(me->query("jueqing_known"))
        {
      		tell_object (me,"绝情的口诀你都已经知道了啊！\n");
      		return 1;
      	}
      	if( !me->query("jueqing/chimeng"))
      	{
      		tell_object (me,"你先去问问痴梦仙姑吧！\n");
      		return 1;
      	}
      	//if( !me->query("jueqing/zhinu"))
      	//	return ("你先去找织女师姐吧！");
      	if( !me->query("jueqing/baihua"))
      	{
      		tell_object (me,"你先去问问百花仙子吧！\n");
      		return 1;
      	}
      	if( !me->query("jueqing/xiwangmu"))
      	{
      		tell_object (me,"你先去问问西王母吧！\n");
      		return 1;
      	}
  if( base_name(environment(me)) != "/d/moon/change_room" || !present("chang e",environment(me)) )
  {
	    tell_object (me,"断肠集最好还是在「长思馆」守着嫦娥读吧！\n");
	    return 1;
  }
  if( ! arg || arg != "book" )
  {
	    tell_object (me,"想读什么呢？\n");
	    return 1;
  }
  if( me->is_busy() )	
  {
	    tell_object (me,"你正忙着呢，没空读书！\n");
	    return 1;
  }
  	me->set_temp("no_move",1);
 	me->start_busy(2+random(2));
 	me->add_temp("read_num",1);
  	message_vision (msgs[random(sizeof(msgs))],me);
  if( random( me->query_temp("read_num") ) > 10 )
  {
  	me->delete_temp("read_num");
  	me->start_busy(5+random(2));
  	me->delete("jueqing/xiwangmu");
  	me->delete("jueqing/chimeng");
  	me->delete("jueqing/baihua");
  	message_vision ("$N叹道：不知情为何物，又如何绝情？\n",me);
  	message_vision ("\n$N细细体味着嫦娥写下的断肠集，只觉字里行间皆是情字，便如一张罗网，密密麻麻将你困在其中！\n",me);
  	if( random(me->query_kar()+me->query("cps")+me->query("cor")) > ( 25 - random(me->query("leaf") + me->query("lunhui_zhuanshi")) ) )
  		call_out("finish_read",2,me);
  	else
  		call_out("finish_read2",2,me);
  }
  return 1;
}
int finish_read( object me )
{
	me->delete_temp("no_move");
	me->set("jueqing_known",1);
	me->delete("leaf");
	message_vision ("$N身陷情网，网中有死结千万，直是剪之不断，理之还乱。\n",me);	
	message_vision ("忽然$N神思闪过一丝清明，$N抓住机缘将这一丝清明化作慧剑，运起全身之力，一剑斩下！\n",me);	
	message_vision ("$N睁开双眸，只见手中空空，身边有若彩蝶飞舞，$N那一击竟将断肠集化为万千碎片！\n",me);	
	message_vision ("嫦娥轻叹一声：这绝情四式$N是学会了，若以后再有所悟，再来找我吧！\n",me);	
	message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗嫦娥(chang e)：" + me->name() + "将月宫武学法术融会贯通，终于学会"+HIB"[绝情四式]"+HIC"！嫦娥轻声叹了一口气！\n\n\n"NOR,users());
	message_vision ("嫦娥清唱道：渺万里层云，千山暮雪，只影向谁去！\n",me);	
	message_vision ("$N听嫦娥那清越淡愁的歌声，似是余意未尽，待要询问，却见嫦娥已径自俯身作书。\n",me);	
	message_vision ("$N轻轻躬身，退了出去。\n",me);	
	me->move("/d/moon/huilang");
	destruct(this_object());
}

int finish_read2( object me )
{
	me->delete_temp("no_move");
	me->set("jueqing_cant",1);
	me->delete("leaf");
	message_vision ("$N身陷情网，网中有死结千万，直是剪之不断，理之还乱。\n",me);	
	message_vision ("$N竭力想要理清其中头绪，却是越陷越深，到得后来，竟然痴痴呆呆，浑然忘我了！\n",me);	
	message_vision ("$N耳边传来一声轻叹，眼前罗袖一闪，身边种种已经消失的无影无踪！\n",me);	
	message_vision ("$N睁开双眸，只见手中空空，嫦娥身前案上正摆着你刚才读的断肠集！\n",me);	
	message_vision ("嫦娥轻叹一声：这绝情四式$N恐怕你是无缘学习了！\n",me);	
	message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗嫦娥(chang e)：" + me->name() + "无法凝慧剑斩情网，终与"+HIB"[绝情四式]"+HIC"无缘！嫦娥轻声叹了一口气！\n\n\n"NOR,users());
	message_vision ("嫦娥清唱道：问世间情为何物，直教生死相许！\n",me);	
	message_vision ("$N听嫦娥着清越淡愁的歌声，不禁痴了。\n",me);	
	message_vision ("嫦娥罗袖一挥，$N后退几步，退出了「长思馆」。\n",me);	
	me->move("/d/moon/huilang");
	destruct(this_object());
}
