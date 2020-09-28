import {KeycloakService} from 'keycloak-angular';
import {environment} from '../environments/environment';

export function initializer(keycloak: KeycloakService) {
  return (): Promise<any> => {
    return new Promise(async (resolve, reject) => {
      try {
        await keycloak.init({
          config: {
            url: environment.keycloak.url,
            realm: environment.keycloak.realm,
            clientId: environment.keycloak.clientId
          },
          enableBearerInterceptor: true,
          bearerExcludedUrls: ['/*']
        });
        resolve();
      } catch (error) {
        reject(error);
      }
    });
  };
}
