$ = jQuery.noConflict(); // Make sure jQuery owns $ here
$.fn.Gpsuperfish = function (op) {
    var sf = $.fn.Gpsuperfish;
    sf.o = [];
    sf.op = {};
    sf.c = {
        menuClass: 'sf-js-enabled',
        isParent: 'sf-parent',
        arrowClass: 'sf-sub-indicator'
    };
    sf.defaults = {
        GpsuperfishWidth: 150,
        multiColumn: true,
        dualColumn: 6,
        tripleColumn: 12,
        hoverClass: 'sfHover',
        delay: 500,
        animationShow: {
            height: 'show'
        },
        speedShow: 600,
        easingShow: 'easeOutBounce',
        animationHide: {
            height: 'hide',
            opacity: 'hide'
        },
        speedHide: 200,
        easingHide: 'easeInTurbo',
        autoArrows: true,
        onShow: function () {},
        onHide: function () {}
    };
    var o = $.extend({}, sf.defaults, op);
    if (!o.GpsuperfishWidth) {
        o.GpsuperfishWidth = $('ul:first li:first', this).width();
    }
    this.each(function () {
        var parentLi = $('li:has(ul)', this);
        parentLi.each(function () {
            if (o.autoArrows) {
                $('>a', this).append('<span class="' + sf.c.arrowClass + '"></span>');
            }
            $(this).addClass(sf.c.isParent);
        });
		var uls = $('ul', this);
		uls.each(function () {
		  $(this).width(o.GpsuperfishWidth);
		});
        var root = this,
            zIndex = 1000;

        function getSubmenu(ele) {
			if (ele.nodeName.toLowerCase() == 'li') {
                var submenu = $('> ul', ele);
                return submenu.length ? submenu[0] : null;
            } else {
                return ele;
            }
        }

        function getActuator(ele) {
            if (ele.nodeName.toLowerCase() == 'ul') {
                return $(ele).parents('li')[0];
            } else {
                return ele;
            }
        }

        function hideGpsuperfishUl() {
            var submenu = getSubmenu(this);
            if (!submenu) return;
            $.data(submenu, 'cancelHide', false);
            setTimeout(function () {
                if (!$.data(submenu, 'cancelHide')) {
                    $(submenu).animate(o.animationHide, o.speedHide, o.easingHide, function () {
                        o.onHide.call(submenu);
                    });
                }
            }, o.delay);
			$(this).removeClass(o.hoverClass);
			if ($(this).parent().parent().get(0).tagName.toLowerCase() == 'li') {
				$('>ul',this).css('left','-999em');
			}
        }

        function showGpsuperfishUl() {
		    var submenu = getSubmenu(this);
			if (!submenu) return;
            $.data(submenu, 'cancelHide', true);
            
			$(submenu).css({
                zIndex: zIndex++
            }).animate(o.animationShow, o.speedShow, o.easingShow, function () {
				o.onShow.call(submenu);
			});
			
			if (this.nodeName.toLowerCase() == 'li') {
                var li = getActuator(this);
                
				$(li).addClass(o.hoverClass);
				if ($(li).parent().parent().get(0).tagName.toLowerCase() == 'li') {
					$('>ul',li).css('left',o.GpsuperfishWidth + 'px');
				}
            }
        }
        $('li', this).hover(showGpsuperfishUl, hideGpsuperfishUl);
    });
};