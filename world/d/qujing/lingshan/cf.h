
#include <zhuanshi.h>
void check_zuochan(object me);
void finish(object me);
void reward(object me);
string chinese_time(int timep);
string *str=({
	        "你慢慢物我两忘。\n",
	        "你觉得一切胜负荣辱都是过眼云烟。\n",
	        "你觉得自己进入了一个前所未有的境界。\n",
	        "你的心境渐渐清明。\n"
	        "你慢慢地领悟到佛的精髓。\n",
	        "你的思绪慢慢宁静下来。\n"
	     });

void init()
{
    add_action("do_zuochan", "zuochan");
    add_action("do_halt", "halt");
}

int do_zuochan()
{       int zuochan_time;

	object me = this_player();
if(me->is_busy())
      {tell_object(me,"你正忙着呢。\n"); 
             return 1;
              }
	
	if (me->query("rulaitask/get"))
	     {tell_object(me,"你有任务在身，定不下神来参悟。\n"); 

	      return 1;
	     }

        if (me->query_temp("zuochan"))
	     {tell_object(me,"你正在坐禅参悟。\n");
	      return 1;
	     }
if(!userp(me)) return 1;

        message_vision("$N盘膝坐在一个蒲团上，潜思入定，开始参悟自己的所作所为。\n",me);
me->start_busy(5);
        me->set_temp("zuochan", 1);
//        if ( !me->query("rulaitask") )  finish(me);
//      else {
          {
        	if (me->query("rulaitask/fail"))
	        zuochan_time = 40+random(40)+time();
	        else zuochan_time = 20+random(20)+time();
	        me->set_temp("zuochan_time",zuochan_time);
	   //     if(wizardp(me))
	   //       write("zuochan_time"+zuochan_time+"\n");
	        check_zuochan(me);
	      }
	             
        return 1;
}


void check_zuochan(object me)
{       
	int zuochan_time = me->query_temp("zuochan_time");
	if ( time()-zuochan_time>0) finish(me);
	
	else {
		if ( !random(6))
	              tell_object(me,str[random(sizeof(str))]);
	  //      if(wizardp(me))
	  //        zuochan_time=time();
	 //         write("zuochan_time"+zuochan_time+"\n");
	call_out("check_zuochan",1,me);
	      }
}

void finish(object me)
{
	tell_object(me,"你只觉灵台一片清明，似乎禅意已尽。\n");
	message_vision("$N深深地吸了口气，站了起来。\n",me);
me->start_busy(2);
        me->delete_temp("zuochan");
        if (me->query("rulaitask/accomplish")) 
        {
        	me->add("rulaitask/success",1);
        	reward(me);
        }
        me->set_temp("success",me->query("rulaitask/success"));
        me->set_temp("oneday",me->query("rulaitask/oneday"));
        me->set_temp("whichdate",me->query("rulaitask/whichdate"));
        me->delete("rulaitask");
        me->set("rulaitask/success",me->query_temp("success"));
        me->set("rulaitask/oneday",me->query_temp("oneday"));
        me->set("rulaitask/whichdate",me->query_temp("whichdate"));
        
        me->delete_temp("success");
        me->delete_temp("oneday");
        me->delete_temp("whichdate");
}

void reward(object me)
{
	int wuxue,level,kind_bonus,level_bonus,timep;
	int extra_bonus,potential_bonus,combat_exp_bonus,daoxing_bonus;
	string str,kind,time,msg;
	
	wuxue = me->query("combat_exp");
	level = me->query("rulaitask/level");
	kind  = me->query("rulaitask/kind");     
        timep = me->query("rulaitask/end_time")-me->query("rulaitask/start_time");
        time  = chinese_time(timep);
        
        if ( level == 1 ) level_bonus=500;
        else if ( level == 2 ) level_bonus=800;
        else level_bonus=1000;
        
        if ( kind == "杀" ) kind_bonus=400;
        else if ( kind == "擒" ) kind_bonus=600;
        else if ( kind == "劝" ) kind_bonus=800;
        else kind_bonus=1000;
        
        //extra_bonus = (me->query("combat_exp")/1000)/3;
        extra_bonus = me->query("combat_exp")/30000;
        extra_bonus += me->query("daoxing")/30000;
        extra_bonus += (zs_getSpentExp(me->query("lunhui_zhuanshi"))+zs_getSpentDx(me->query("lunhui_zhuanshi")))/30000;
        extra_bonus = extra_bonus/2;
//if(extra_bonus > 2000) extra_bonus = 2000;//太高了,比原来翻了一倍!!!
//if(extra_bonus > 1000) extra_bonus = 1000;
        potential_bonus = (level_bonus + kind_bonus + extra_bonus/2)/2 + random(level_bonus + kind_bonus + extra_bonus)/4;
        combat_exp_bonus = level_bonus*4 + kind_bonus*3  + extra_bonus*2 + random(level_bonus + kind_bonus + extra_bonus)/2;
        daoxing_bonus = level_bonus*4 + kind_bonus*3  + extra_bonus*2 + random(level_bonus + kind_bonus + extra_bonus)/2;
        potential_bonus = potential_bonus / 2;
        combat_exp_bonus = combat_exp_bonus / 2;
        daoxing_bonus = daoxing_bonus / 2;
	if(potential_bonus > 2000) potential_bonus = 2000 + random(401);
	if(combat_exp_bonus > 10000) combat_exp_bonus = 10000 + random(2000);
	if(daoxing_bonus > 10000) daoxing_bonus = 10000 + random(2000);
        me->add("potential", potential_bonus);
        me->add("combat_exp", combat_exp_bonus);
        me->add("daoxing", daoxing_bonus);
        me->add("balance",100000);
        str = "得到了"+potential_bonus+"点潜能，";
        str +=combat_exp_bonus+"武学经验，";
        str += COMBAT_D->chinese_daoxing(daoxing_bonus)+"道行，十两黄金。";
        
        tell_object(me,"你得到了"+potential_bonus+"点潜能，"+combat_exp_bonus+"武学经验，"+COMBAT_D->chinese_daoxing(daoxing_bonus)+"道行，十两黄金。\n");
        str = me->name()+"完成了一个难度"+chinese_number(level)+"的"+kind+"妖任务，" + str+ "用时"+time+"。";
        if ( level > 1 ) CHANNEL_D->do_channel(me, "rumor",str);
        
       // str = str + "用时"+time+"。";
        MONITOR_D->report_system_msg (str);
        
        switch (kind)
          {case "杀": {
          	        me->add("rulaitask_log/kill_potential",potential_bonus);
                        me->add("rulaitask_log/kill_combat",combat_exp_bonus);
                        me->add("rulaitask_log/kill_daoxing",daoxing_bonus);
          	
          	        switch (level)
                            {case 1:{me->add("rulaitask_log/kill1",1);
                                     break;
                                     }
                              case 2:{me->add("rulaitask_log/kill2",1);
                                      break;
                                     }
                              case 3: me->add("rulaitask_log/kill3",1);
                             }
                         break;
                      }
          case "擒": {
          	        me->add("rulaitask_log/arrest_potential",potential_bonus);
                        me->add("rulaitask_log/arrest_combat",combat_exp_bonus);
                        me->add("rulaitask_log/arrest_daoxing",daoxing_bonus);
          	
          	        switch (level)
                            {case 1:{me->add("rulaitask_log/arrest1",1);
                                     break;
                                     }
                              case 2:{me->add("rulaitask_log/arrest2",1);
                                      break;
                                     }
                              case 3: me->add("rulaitask_log/arrest3",1);
                             }
                         break;
                      }
          case "劝": {
          	        me->add("rulaitask_log/persuade_potential",potential_bonus);
                        me->add("rulaitask_log/persuade_combat",combat_exp_bonus);
                        me->add("rulaitask_log/persuade_daoxing",daoxing_bonus);
          	
          	        switch (level)
                            {case 1:{me->add("rulaitask_log/persuade1",1);
                                     break;
                                     }
                              case 2:{me->add("rulaitask_log/persuade2",1);
                                      break;
                                     }
                              case 3: me->add("rulaitask_log/persuade3",1);
                             }
                         break;
                      }
          case "降": {
          	        me->add("rulaitask_log/fight_potential",potential_bonus);
                        me->add("rulaitask_log/fight_combat",combat_exp_bonus);
                        me->add("rulaitask_log/fight_daoxing",daoxing_bonus);
          	
          	        switch (level)
                            {case 1:{me->add("rulaitask_log/fight1",1);
                                     break;
                                     }
                              case 2:{me->add("rulaitask_log/fight2",1);
                                      break;
                                     }
                              case 3: me->add("rulaitask_log/fight3",1);
                             }
                     }                        
          }
}                               

int do_halt()
{
	object me = this_player();
if(me->is_busy())
          {tell_object(me,"你正忙着呢。\n"); 
           return 1;      }
	if (me->query_temp("zuochan"))
	   {remove_call_out("check_zuochan");
me->start_busy(2);
	    me->delete_temp("zuochan_time");
            message_vision("$N深深地吸了口气，站了起来。\n",me);
            me->delete_temp("no_move");
            me->delete_temp("zuochan");
            return 1;
           }
         else return 0;
}       
        


string chinese_time(int timep)
{
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if(d) time = chinese_number(d) + "天";
        else time = "";

        if(h) time += chinese_number(h) + "小时";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";
        
        return time;
}


int valid_leave(object who, string dir)
{
        if (who->query_temp("zuochan"))
        return notify_fail("燃灯古佛拦着你：坐禅时还乱动！\n");
        else 
              return ::valid_leave(who, dir);
}
