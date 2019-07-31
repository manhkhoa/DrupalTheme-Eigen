(function($) {
	$(document).ready(function() {
		/* prepend menu icon */
		$('#menu-bar').prepend('<div id="menu-icon">Menu</div>');
		/* toggle nav */
		$("#menu-icon").click( function(){
			$("#menu-bar ul.menu").slideToggle();
			if($(this).hasClass("active"))
				$(this).removeClass("active");
			else
				$(this).addClass("active");
		});
		//Show & Hide #menu-icon
		var width = window.innerWidth || document.documentElement.clientWidth;
		if(width > 480){
			$('#menu-icon').hide();
			$('#menu-bar>.menu').show();
		}
		else {
			$('#menu-icon').show();
			$('#menu-bar>.menu').hide();
		}
		//Show & Hide #menu-icon when resize windows
		$(window).resize(function() {
			var width = window.innerWidth || document.documentElement.clientWidth;
			//only use window.innerWidth beacause don't need Fix Menu-Reponsive on IE 8
			if(width > 480){
				$('#menu-icon').hide();
				$('#menu-bar>.menu').show();
			}
			else {
				$('#menu-icon').show();
				$('#menu-bar>.menu').hide();
			}
		});
	});
})(jQuery);