var body = document.querySelector('body');

// Popup feedback form
var formOpenBtn = document.querySelector('.header_feedback-link');
var feedbackForm = document.querySelector('.feedback');
var formCloseBtn = document.querySelector('.feedback_close-btn');
var input = document.querySelectorAll('.feedback_input');

function showForm(event) {
  event.preventDefault();
  body.classList.add('overlay');
  feedbackForm.classList.add('feedback_visible');
  input[0].focus();
  feedbackForm.classList.add('feedback_animate');
}
function closeForm(event) {
  event.preventDefault();
  feedbackForm.classList.remove('feedback_animate');
  feedbackForm.classList.remove('feedback_visible');
  body.classList.remove('overlay');
}
function closeFormEsc(event) {
  if (event.keyCode == 27) {
    feedbackForm.classList.remove('feedback_animate');
    feedbackForm.classList.remove('feedback_visible');
    body.classList.remove('overlay');
  }
}

formOpenBtn.addEventListener('click', showForm);
formCloseBtn.addEventListener('click', closeForm);
window.addEventListener('keydown', closeFormEsc);


// Slides
var slides = document.querySelectorAll('.slider_slide');
var currentSlide = 1;
var slideInterval = setInterval(nextSlide, 4000);
var next = document.querySelector('.slider_control_prev');
var previous = document.querySelector('.slider_control_next');

next.addEventListener("click", nextSlide);
previous.addEventListener("click", previousSlide);

function nextSlide() {
    clearInterval(slideInterval);
    goToSlide(currentSlide + 1);
}
function previousSlide() {
    clearInterval(slideInterval);
    goToSlide(currentSlide - 1);
}
function goToSlide(n) {
    slideInterval = setInterval(nextSlide, 4000);
    slides[currentSlide].classList.remove('slider_slide_middle');
	slides[(currentSlide + 1)%slides.length].classList.remove('slider_slide_right');
    slides[(currentSlide - 1 + slides.length)%slides.length].classList.remove('slider_slide_left');
    currentSlide = (n+slides.length)%slides.length;
	slides[currentSlide].classList.add('slider_slide_middle');
	slides[(currentSlide + 1)%slides.length].classList.add('slider_slide_right');
    slides[(currentSlide - 1 + slides.length)%slides.length].classList.add('slider_slide_left');
    /*slides[currentSlide].classList.add('slider_slide_show');*/
}


/* onLoad */
/* List */

var coll = document.querySelectorAll(".content_nav-aside-link");

function loadPage() {
	displayItems(1);
	
    var i;
    for (i = 0; i < coll.length; i++) {
		
        coll[i].addEventListener("click", function() {
    
            var content = this.nextElementSibling;
            if (content.style.maxHeight != "0px"){
				content.style.maxHeight = "0px";
            } else {
				content.style.maxHeight = "1000px";
            }
        });
		var content = coll[i].nextElementSibling;
		if (i != 0) content.style.maxHeight = "0px";
    }
}

/*  Pages */
function displayItems(sender) {
	
    var items = document.querySelectorAll(".content_item");
    var itemsPerPage = 6;
    var minIndex = itemsPerPage * (sender - 1);
    var maxIndex = itemsPerPage * sender;

    for (let i = 0; i < items.length; i++) {
        items[i].style.display = "none";
    }
    for (let i = minIndex; i < maxIndex && i < items.length; i++) {
        items[i].style.display = "inline-block";
    }
	var pages = document.querySelectorAll(".content_page-number");
	for (let i = 0; i < pages.length; i++) {
		
        pages[i].classList.remove("content_page-number_current");
    }
	pages[sender - 1].classList.add("content_page-number_current");
}


/* buy */

function buy(){
	alert("Нужно больше золота!!!");
}