import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams } from 'ionic-angular';
import { LoginPage } from '../login/login';
import { ParticleProvider } from '../../providers/particle/particle';

@IonicPage()
@Component({
  selector: 'page-variable',
  templateUrl: 'variable.html',
})
export class VariablePage {

  public uv: any;                     // Contains the value of our cloud variable
  public subscribed: boolean = false;
  public subscription: any = null;     // Maintains the subscription variable updates

  constructor(public navCtrl: NavController, public navParams: NavParams, public particle: ParticleProvider) {
  }

  ionViewDidLoad() {
    // Make sure we are logged in to our Particle account
    if (!this.particle.token) {
    	this.login()
    }
  }

  // Cancel any current subscriptions to our variable
  cancelSubscription() {
    if (this.subscription && this.subscription.cancel) {
        this.subscription.cancel();
    }
    this.subscription = null;
  }

  ionViewDidEnter() {
    // When entering the page, subscribe to updates to the Particle cloud varibale uv
    if (this.particle.device) {
        this.cancelSubscription();
        this.subscription = this.particle.pollVariable("uv").subscribe(
            (value) => { this.uv = value; this.subscribed = true; },
            (error) => { console.log("Error reading uv"); this.subscribed = false; },
            () => { console.log("Stopped polling uv"); this.subscribed = false; }
        );
    }
  }

  login() {
    this.navCtrl.push( LoginPage );
  }

}
